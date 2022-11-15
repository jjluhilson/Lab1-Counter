module top #(
  parameter WIDTH = 8,
  parameter DIGITS = 3
)(
  // interface signals
  input  wire             clk,      // clock 
  input  wire             rst,      // reset 
  input  wire             en,       // enable
  input  wire [WIDTH-1:0] v,        // value to preload
  output wire [11:0]      bcd       // count output
);

  wire  [WIDTH-1:0]       count;    // interconnect wire

counter myCounter (
  .clk (clk),
  .rst (rst),
  .en (en),
  .count (count)
);

bin2bcd myDecoder (
  .x (count),
  .BCD (bcd)
);

endmodule