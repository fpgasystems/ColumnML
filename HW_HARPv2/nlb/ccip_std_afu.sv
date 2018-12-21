// ***************************************************************************
// Copyright (c) 2013-2016, Intel Corporation
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// * Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// * Redistributions in binary form must reproduce the above copyright notice,
// this list of conditions and the following disclaimer in the documentation
// and/or other materials provided with the distribution.
// * Neither the name of Intel Corporation nor the names of its contributors
// may be used to endorse or promote products derived from this software
// without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// Module Name:     ccip_std_afu
// Project :        ccip afu top 
// Description :    This module instantiates CCI-P compliant AFU

// ***************************************************************************
import ccip_if_pkg::*;
module ccip_std_afu(
  // CCI-P Clocks and Resets
  input           logic             pClk,              // 400MHz - CCI-P clock domain. Primary interface clock
  input           logic             pClkDiv2,          // 200MHz - CCI-P clock domain.
  input           logic             pClkDiv4,          // 100MHz - CCI-P clock domain.
  input           logic             uClk_usr,          // User clock domain. Refer to clock programming guide  ** Currently provides fixed 272.78MHz clock **
  input           logic             uClk_usrDiv2,      // User clock domain. Half the programmed frequency  ** Currently provides fixed 136.37MHz clock **
  input           logic             pck_cp2af_softReset,      // CCI-P ACTIVE HIGH Soft Reset
  input           logic [1:0]       pck_cp2af_pwrState,       // CCI-P AFU Power State
  input           logic             pck_cp2af_error,          // CCI-P Protocol Error Detected

  // Interface structures
  input           t_if_ccip_Rx      pck_cp2af_sRx,        // CCI-P Rx Port
  output          t_if_ccip_Tx      pck_af2cp_sTx         // CCI-P Tx Port
);

//===============================================================================================
// User AFU goes here
//===============================================================================================
// NOTE: All inputs and outputs in PR region (AFU) must be registered
// NLB AFU registers all its outputs therefore not registered again here.
// Registering Inputs to AFU

logic          pck_cp2af_softReset_T1;
t_if_ccip_Rx   pck_cp2af_sRx_T1;

always@(posedge pClk)
begin
    pck_cp2af_sRx_T1           <= pck_cp2af_sRx;
    pck_cp2af_softReset_T1     <= pck_cp2af_softReset;
end

// ================================================================
// NLB AFU- provides validation, performance characterization modes 
// It also serves as a reference design
// ================================================================

nlb_lpbk nlb_lpbk(
  .Clk_400             ( pClk ) ,
  .Clk_200             ( pClkDiv2 ) ,
  .SoftReset           ( pck_cp2af_softReset_T1 ) ,

  .cp2af_sRxPort       ( pck_cp2af_sRx_T1 ) ,
  .af2cp_sTxPort       ( pck_af2cp_sTx ) 
);

/*
reg                   clock_200;
logic                 pck_cp2af_softReset_200;
t_if_ccip_Rx          pck_cp2af_sRx_200;
t_if_ccip_Rx[15:0]    pck_cp2af_sRx_cross;
t_if_ccip_Tx          pck_af2cp_sTx_200;

always@(clock_200)
begin
  if (clock_200 == 1'b1) begin
    pck_af2cp_sTx <= pck_af2cp_sTx_200;
  end
  else begin
    pck_af2cp_sTx <= 0;
  end
end

reg[3:0]      wpointer;
reg[3:0]      rpointer;

always@(posedge pClk)
begin
  if (pck_cp2af_softReset == 1'b1) begin
    clock_200 <= 1'b0;
    wpointer <= 0;
  end
  else begin
    clock_200 <= !clock_200;

    if ( pck_cp2af_sRx.c0.rspValid == 1'b1 || pck_cp2af_sRx.c0.mmioRdValid == 1'b1 || pck_cp2af_sRx.c0.mmioWrValid == 1'b1 || pck_cp2af_sRx.c1.rspValid == 1'b1 ) begin
      pck_cp2af_sRx_cross[wpointer] <= pck_cp2af_sRx;
      wpointer <= wpointer+1;
    end
  end
end

always@(posedge pClkDiv2)
begin
  pck_cp2af_softReset_200 <= pck_cp2af_softReset;

  if (pck_cp2af_softReset == 1) begin
    rpointer <= 0;
  end
  else begin
    pck_cp2af_sRx_200 <= 0;
    if (rpointer != wpointer) begin
      pck_cp2af_sRx_200 <= pck_cp2af_sRx_cross[rpointer];
      rpointer <= rpointer+1;
    end
  end
end

nlb_lpbk nlb_lpbk(
  .Clk_400             ( pClkDiv2 ) ,
  .Clk_200             ( pClkDiv2 ) ,
  .SoftReset           ( pck_cp2af_softReset_200 ) ,

  .cp2af_sRxPort       ( pck_cp2af_sRx_200 ) ,
  .af2cp_sTxPort       ( pck_af2cp_sTx_200 ) 
);
*/

// ================================================================
// ccip_debug is a reference debug module for tapping cci-p signals
// User AFUs can choose to use this or Tap their own signals
// ================================================================
/*
ccip_debug inst_ccip_debug(
  .pClk                (pClk),        
  .pck_cp2af_pwrState  (pck_cp2af_pwrState),
  .pck_cp2af_error     (pck_cp2af_error),

  .pck_cp2af_sRx       (pck_cp2af_sRx),   
  .pck_af2cp_sTx       (pck_af2cp_sTx)    
);
*/
endmodule
