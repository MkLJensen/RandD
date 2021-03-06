`ifndef REPLACE_WITH_MODULE_VLD_RDY_DATA_TRACE_INTERFACE__SV
`define REPLACE_WITH_MODULE_VLD_RDY_DATA_TRACE_INTERFACE__SV

interface REPLACE_WITH_MODULE_vld_rdy_data_trace_interface #(int DATAW=8) ();
//timeunit 1ps;
//timeprecision  1ps;
    logic    clk     ;
    logic    rst     ;
    logic    ready   ;
    logic    valid   ;
    logic[DATAW-1:0] data;
    longint clkcnt;

initial begin
    clkcnt = 0;
    forever begin
        @(posedge clk);
        #1ps;
        clkcnt++;
    end
end
endinterface
`endif
