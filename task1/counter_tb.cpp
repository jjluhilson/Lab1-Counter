#include "Vcounter.h" //VCounter.h for counter module
#include "verilated.h"
#include "verilated_vcd_c.h"

int main (int argc, char **argv, char **env) {
    int i; //counts the number of clock cycles to simulate (used in for loop)
    int clk; //clock signal

    Verilated::commandArgs(argc, argv);
    //init top verilog instance
    Vcounter* top = new Vcounter; //instantiate the counter module as Vcounter - name of all generated files. This is the DUT
    //init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC; //vcdC is the data type we use for the trace file pointer
    top->trace (tfp, 99);
    tfp->open ("counter.vcd"); //dump the waveform data to counter.vcd

    //initalize simulation inputs
    top->clk = 1; //top is the name of the top level entity. Only top level signals are visible
    top->rst = 1;
    top->en = 0;

    //run simulation for many clock cycles
    for (i = 0; i < 300; i++) {

        //dump variables into VCD file and toggle clock
        for (clk = 0; clk < 2; clk++) { //for loop that toggles the clock, also outputs trace for each half of the clock cycle. Forces model to evaluate on both edges of the clock
            tfp->dump (2*i + clk); //unit is in picoseconds!
            top->rst = (i < 2) | (i == 20 && clk == 0);
            top->clk = !top->clk;
            top->eval(); //simulates clock cycle in verilator
        }

        //we change the rst and en signals throughout the simulation
        //top->rst = (i < 2) | (i == 19);
        top->en = (i>4) & ((i < 14) | (i > 16));
        if (Verilated::gotFinish()) exit(0);
    }
    tfp->close();
    exit(0);
}