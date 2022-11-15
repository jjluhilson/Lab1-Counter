module counter #( //module name must be same as file name
    parameter WIDTH = 8
)(
    // interface signals
    input logic clk, //clock
    input logic rst, //reset
    input logic en, //counter enable,
    output logic [WIDTH-1:0] count //count output
);

always_ff @ (posedge clk, posedge rst)
    if (rst) count <= {WIDTH{1'b0}}; // <= means non-blocking assignment
    else count <= count + {{WIDTH-1{1'b0}}, en}; //concatenation between all 0s with the en at the end - add to counter 1 if enabled, or 0 if not.

endmodule
