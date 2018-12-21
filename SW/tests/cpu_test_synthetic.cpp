// Copyright (C) 2018 Kaan Kara - Systems Group, ETH Zurich

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.

// You should have received a copy of the GNU Affero General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
//*************************************************************************

#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#include "../src/scd.h"

using namespace std;

#define NUM_VALUES_PER_LINE 16
#define VALUE_TO_INT_SCALER 10

int main(int argc, char* argv[]) {

	cpu_set_t cpuset;
	pthread_t thread = pthread_self();
	pthread_attr_t attr;
	pthread_getattr_np(thread, &attr);
	CPU_ZERO(&cpuset);
	CPU_SET(0, &cpuset);
	pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &cpuset);

	char* pathToDataset;
	uint32_t numSamples;
	uint32_t numFeatures;
	uint32_t miniBatchSize = 16384;
	uint32_t numInstances = 1;
	char doLogreg = 0;
	if (argc != 5) {
		cout << "Usage: ./app <numSamples> <numFeatures> <miniBatchSize> <logreg>" << endl;
		return 0;
	}
	else {
		numSamples = atoi(argv[1]);
		numFeatures = atoi(argv[2]);
		miniBatchSize = atoi(argv[3]);
		doLogreg = (char)atoi(argv[4]);
	}

	uint32_t stepSizeShifter = 2;
	uint32_t numEpochs = 5;
	uint32_t numMinibatchesAtATime = 1;
	uint32_t residualUpdatePeriod = 100;
	float lambda = 0.1;

	scd scd_app(0);
	scd_app.generate_synthetic_data(numSamples, numFeatures, 0);

	uint32_t useEncryption;
	uint32_t useCompression ;
	for (char doRealSCD = 0; doRealSCD < 2; doRealSCD++) {
		useEncryption = 0;
		useCompression = 0;
		// if (doRealSCD == 0) {
		// 	if (doLogreg == 1)
		// 		scd_app.float_logreg_SCD(NULL, numEpochs, miniBatchSize, residualUpdatePeriod, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER);
		// 	else
		// 		scd_app.float_linreg_SCD(NULL, numEpochs, miniBatchSize, numMinibatchesAtATime, residualUpdatePeriod, 1.0/(1 << stepSizeShifter), useEncryption, useCompression, VALUE_TO_INT_SCALER);
		// }
		// else {
		// 	if (doLogreg == 1)
		// 		scd_app.float_logreg_SCD(NULL, numEpochs, numSamples, residualUpdatePeriod, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER);
		// 	else
		// 		scd_app.float_linreg_SCD(NULL, numEpochs, numSamples, numMinibatchesAtATime, residualUpdatePeriod, 1.0/(1 << stepSizeShifter), useEncryption, useCompression, VALUE_TO_INT_SCALER);
		// }
		scd_app.AVXmulti_float_linlogreg_SCD(NULL, doRealSCD, doLogreg, numEpochs, miniBatchSize, numEpochs+1, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER, 1);
		scd_app.AVXmulti_float_linlogreg_SCD(NULL, doRealSCD, doLogreg, numEpochs, miniBatchSize, numEpochs+1, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER, 2);
		scd_app.AVXmulti_float_linlogreg_SCD(NULL, doRealSCD, doLogreg, numEpochs, miniBatchSize, numEpochs+1, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER, 4);
		scd_app.AVXmulti_float_linlogreg_SCD(NULL, doRealSCD, doLogreg, numEpochs, miniBatchSize, numEpochs+1, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER, 8);
		scd_app.AVXmulti_float_linlogreg_SCD(NULL, doRealSCD, doLogreg, numEpochs, miniBatchSize, numEpochs+1, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER, 14);

		useEncryption = 1;
		useCompression = 0;
		scd_app.encrypt_a(miniBatchSize, useCompression);
		// if (doRealSCD == 0) {
		// 	if (doLogreg == 1)
		// 		scd_app.float_logreg_SCD(NULL, numEpochs, miniBatchSize, residualUpdatePeriod, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER);
		// 	else
		// 		scd_app.float_linreg_SCD(NULL, numEpochs, miniBatchSize, numMinibatchesAtATime, residualUpdatePeriod, 1.0/(1 << stepSizeShifter), useEncryption, useCompression, VALUE_TO_INT_SCALER);
		// }
		// else {
		// 	if (doLogreg == 1)
		// 		scd_app.float_logreg_SCD(NULL, numEpochs, numSamples, residualUpdatePeriod, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER);
		// 	else
		// 		scd_app.float_linreg_SCD(NULL, numEpochs, numSamples, numMinibatchesAtATime, residualUpdatePeriod, 1.0/(1 << stepSizeShifter), useEncryption, useCompression, VALUE_TO_INT_SCALER);
		// }
		scd_app.AVXmulti_float_linlogreg_SCD(NULL, doRealSCD, doLogreg, numEpochs, miniBatchSize, numEpochs+1, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER, 1);
		scd_app.AVXmulti_float_linlogreg_SCD(NULL, doRealSCD, doLogreg, numEpochs, miniBatchSize, numEpochs+1, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER, 2);
		scd_app.AVXmulti_float_linlogreg_SCD(NULL, doRealSCD, doLogreg, numEpochs, miniBatchSize, numEpochs+1, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER, 4);
		scd_app.AVXmulti_float_linlogreg_SCD(NULL, doRealSCD, doLogreg, numEpochs, miniBatchSize, numEpochs+1, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER, 8);
		scd_app.AVXmulti_float_linlogreg_SCD(NULL, doRealSCD, doLogreg, numEpochs, miniBatchSize, numEpochs+1, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER, 14);

		useEncryption = 0;
		useCompression = 1;
		float compressionRate = scd_app.compress_a(miniBatchSize, VALUE_TO_INT_SCALER);
		cout << "compressionRate: " << compressionRate << endl;
		// if (doRealSCD == 0) {
		// 	if (doLogreg == 1)
		// 		scd_app.float_logreg_SCD(NULL, numEpochs, miniBatchSize, residualUpdatePeriod, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER);
		// 	else
		// 		scd_app.float_linreg_SCD(NULL, numEpochs, miniBatchSize, numMinibatchesAtATime, residualUpdatePeriod, 1.0/(1 << stepSizeShifter), useEncryption, useCompression, VALUE_TO_INT_SCALER);
		// }
		// else {
		// 	if (doLogreg == 1)
		// 		scd_app.float_logreg_SCD(NULL, numEpochs, numSamples, residualUpdatePeriod, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER);
		// 	else
		// 		scd_app.float_linreg_SCD(NULL, numEpochs, numSamples, numMinibatchesAtATime, residualUpdatePeriod, 1.0/(1 << stepSizeShifter), useEncryption, useCompression, VALUE_TO_INT_SCALER);
		// }
		scd_app.AVXmulti_float_linlogreg_SCD(NULL, doRealSCD, doLogreg, numEpochs, miniBatchSize, numEpochs+1, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER, 1);
		scd_app.AVXmulti_float_linlogreg_SCD(NULL, doRealSCD, doLogreg, numEpochs, miniBatchSize, numEpochs+1, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER, 2);
		scd_app.AVXmulti_float_linlogreg_SCD(NULL, doRealSCD, doLogreg, numEpochs, miniBatchSize, numEpochs+1, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER, 4);
		scd_app.AVXmulti_float_linlogreg_SCD(NULL, doRealSCD, doLogreg, numEpochs, miniBatchSize, numEpochs+1, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER, 8);
		scd_app.AVXmulti_float_linlogreg_SCD(NULL, doRealSCD, doLogreg, numEpochs, miniBatchSize, numEpochs+1, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER, 14);

		useEncryption = 1;
		useCompression = 1;
		scd_app.encrypt_a(miniBatchSize, useCompression);
		// if (doRealSCD == 0) {
		// 	if (doLogreg == 1)
		// 		scd_app.float_logreg_SCD(NULL, numEpochs, miniBatchSize, residualUpdatePeriod, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER);
		// 	else
		// 		scd_app.float_linreg_SCD(NULL, numEpochs, miniBatchSize, numMinibatchesAtATime, residualUpdatePeriod, 1.0/(1 << stepSizeShifter), useEncryption, useCompression, VALUE_TO_INT_SCALER);
		// }
		// else {
		// 	if (doLogreg == 1)
		// 		scd_app.float_logreg_SCD(NULL, numEpochs, numSamples, residualUpdatePeriod, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER);
		// 	else
		// 		scd_app.float_linreg_SCD(NULL, numEpochs, numSamples, numMinibatchesAtATime, residualUpdatePeriod, 1.0/(1 << stepSizeShifter), useEncryption, useCompression, VALUE_TO_INT_SCALER);
		// }
		scd_app.AVXmulti_float_linlogreg_SCD(NULL, doRealSCD, doLogreg, numEpochs, miniBatchSize, numEpochs+1, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER, 1);
		scd_app.AVXmulti_float_linlogreg_SCD(NULL, doRealSCD, doLogreg, numEpochs, miniBatchSize, numEpochs+1, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER, 2);
		scd_app.AVXmulti_float_linlogreg_SCD(NULL, doRealSCD, doLogreg, numEpochs, miniBatchSize, numEpochs+1, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER, 4);
		scd_app.AVXmulti_float_linlogreg_SCD(NULL, doRealSCD, doLogreg, numEpochs, miniBatchSize, numEpochs+1, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER, 8);
		scd_app.AVXmulti_float_linlogreg_SCD(NULL, doRealSCD, doLogreg, numEpochs, miniBatchSize, numEpochs+1, 1.0/(1 << stepSizeShifter), lambda, useEncryption, useCompression, VALUE_TO_INT_SCALER, 14);
	}
}
