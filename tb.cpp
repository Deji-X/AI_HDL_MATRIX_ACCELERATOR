#include "VAcceleratorMM.h"
#include "verilated.h"
#include <iostream>

vluint64_t main_time = 0;

double sc_time_stamp() { return main_time; }

void tick(VAcceleratorMM* top) {
    top->clk = 0;
    top->eval();
    main_time++;

    top->clk = 1;
    top->eval();
    main_time++;
}

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);

    VAcceleratorMM* top = new VAcceleratorMM;

    // Reset
    top->rst_n = 0;
    tick(top);
    top->rst_n = 1;

    // Write 5 to address 0
    top->address = 0;
    top->data_in = 5;
    top->data_write_n = 0b00;  
    tick(top);

    top->data_write_n = 0b11;

    // Apply ui_in = 10
    top->ui_in = 10;
    tick(top);

    std::cout << "uo_out = " << (int)top->uo_out << std::endl;

    delete top;
    return 0;
}
