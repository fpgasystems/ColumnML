# MIT License

# Copyright (c) 2018 FPGA @ Systems Group, ETH Zurich

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#*************************************************************************

CXX			= g++
CPPFLAGS	= -O3 -std=c++11 -march=native -Wall -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-function -Wno-reorder -Wno-narrowing -DAVX2
LDFLAGS		= -lpthread -lOSAL -lAAS
COMMON		= ./driver/iFPGA.cpp ./driver/RuntimeClient.cpp 

.PHONY: all clean distclean

all: all_scd_tests

all_scd_tests: ./tests/period_analysis.cpp ./tests/decomprate_analysis.cpp ./tests/numsamples_analysis.cpp ./tests/numfeatures_analysis.cpp ./tests/scratch.cpp ./tests/cpu_test_synthetic.cpp ./tests/fscd_test_synthetic.cpp ./tests/fscd_test_raw.cpp ./tests/prediction_test.cpp ./tests/scd_vs_miniscd_test.cpp $(COMMON) ./src/scd.h
	$(CXX) -D HARPv2 -I$(AALSDK)/include $(CPPFLAGS) ./tests/period_analysis.cpp $(COMMON) -o period_analysis -L$(AALSDK)/lib $(LDFLAGS) -laalrt
	$(CXX) -D HARPv2 -I$(AALSDK)/include $(CPPFLAGS) ./tests/decomprate_analysis.cpp $(COMMON) -o decomprate_analysis -L$(AALSDK)/lib $(LDFLAGS) -laalrt
	$(CXX) -D HARPv2 -I$(AALSDK)/include $(CPPFLAGS) ./tests/numsamples_analysis.cpp $(COMMON) -o numsamples_analysis -L$(AALSDK)/lib $(LDFLAGS) -laalrt
	$(CXX) -D HARPv2 -I$(AALSDK)/include $(CPPFLAGS) ./tests/numfeatures_analysis.cpp $(COMMON) -o numfeatures_analysis -L$(AALSDK)/lib $(LDFLAGS) -laalrt
	$(CXX) -D HARPv2 -I$(AALSDK)/include $(CPPFLAGS) ./tests/scratch.cpp $(COMMON) -o scratch -L$(AALSDK)/lib $(LDFLAGS) -laalrt
	$(CXX) -D HARPv2 -I$(AALSDK)/include $(CPPFLAGS) ./tests/cpu_test_synthetic.cpp $(COMMON) -o cpu_test_synthetic -L$(AALSDK)/lib $(LDFLAGS) -laalrt
	$(CXX) -D HARPv2 -I$(AALSDK)/include $(CPPFLAGS) ./tests/fscd_test_synthetic.cpp $(COMMON) -o fscd_test_synthetic -L$(AALSDK)/lib $(LDFLAGS) -laalrt
	$(CXX) -D HARPv2 -I$(AALSDK)/include $(CPPFLAGS) ./tests/fscd_test_raw.cpp $(COMMON) -o fscd_test_raw -L$(AALSDK)/lib $(LDFLAGS) -laalrt
	$(CXX) -D HARPv2 -I$(AALSDK)/include $(CPPFLAGS) ./tests/prediction_test.cpp $(COMMON) -o prediction_test -L$(AALSDK)/lib $(LDFLAGS) -laalrt
	$(CXX) -D HARPv2 -I$(AALSDK)/include $(CPPFLAGS) ./tests/scd_vs_miniscd_test.cpp $(COMMON) -o scd_vs_miniscd_test -L$(AALSDK)/lib $(LDFLAGS) -laalrt

clean:
	rm period_analysis
	rm decomprate_analysis
	rm numsamples_analysis
	rm numfeatures_analysis
	rm scratch
	rm cpu_test_synthetic
	rm fscd_test_synthetic
	rm fscd_test_raw
	rm prediction_test
	rm scd_vs_miniscd_test