#include "Vtop.h" //VCounter.h for counter module
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main (int argc, char **argv, char **env) {
    int i; //counts the number of clock cycles to simulate (used in for loop)
    int clk; //clock signal

    Verilated::commandArgs(argc, argv);
    //init top verilog instance
    Vtop* top = new Vtop; //instantiate the counter module as Vcounter - name of all generated files. This is the DUT
    //init trace dump
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC; //vcdC is the data type we use for the trace file pointer
    top->trace (tfp, 99);
    tfp->open ("counter.vcd"); //dump the waveform data to counter.vcd

    //init vbuddy - port path is in vbuddy.cfg
    if (vbdOpen() != 1) return(-1); //open vbd port, if not found then exit with error code
    vbdHeader("Lab 1: Counter");

    //initalize simulation inputs
    top->clk = 1; //top is the name of the top level entity. Only top level signals are visible
    top->rst = 1;
    top->en = 0;

    //run simulation for many clock cycles
    for (i = 0; i < 300; i++) {

        //dump variables into VCD file and toggle clock
        for (clk = 0; clk < 2; clk++) { //for loop that toggles the clock, also outputs trace for each half of the clock cycle. Forces model to evaluate on both edges of the clock
            tfp->dump (2*i + clk); //unit is in picoseconds!
            top->clk = !top->clk;
            top->eval (); //simulates clock cycle in verilator
        }

        //send count value to Vbuddy
        vbdHex(4, (int(top->bcd) >> 16) & 0xF);
        vbdHex(3, (int(top->bcd) >> 8) & 0xF);
        vbdHex(2, (int(top->bcd) >> 4) & 0xF);
        vbdHex(1, int(top->bcd) & 0xF);
        // vbdPlot(int(top->count), 0, 255);
        vbdCycle(i+1);

        vbdSetMode(0);
        
        //we change the rst and en signals throughout the simulation
        top->rst = (i < 2) | (i == 15);
        top->en = vbdFlag();
        if (Verilated::gotFinish()) exit(0);
    }

    vbdClose();
    tfp->close();
    exit(0);
}