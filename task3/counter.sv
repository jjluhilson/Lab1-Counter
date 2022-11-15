module counter #( //module name must be same as file name
    parameter WIDTH = 8
)(
    // interface signals
    input logic clk, //clock
    input logic rst, //reset
    input logic en, //counter enable,
    input logic [WIDTH-1:0] vbdValue,
    output logic [WIDTH-1:0] count //count output
);

always_ff @ (posedge clk, posedge rst)

    if (rst) count <= {WIDTH{1'b0}};
    else if (en) count <= count + {{WIDTH-1{1'b0}}, 1'b1};

endmodule
