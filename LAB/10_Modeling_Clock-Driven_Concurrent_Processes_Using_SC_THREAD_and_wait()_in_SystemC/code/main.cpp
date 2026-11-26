#include <systemc>
#include <iostream>
using namespace sc_core;
using namespace std;

SC_MODULE(testbench)
{
    sc_clock clk;
    sc_signal<int> count1, count2;

    SC_CTOR(testbench) : clk("clk", 10, SC_NS)
    {
        SC_THREAD(process1);
        SC_THREAD(process2);
    }

    void process1()
    {
        int i = 0;

        while (true)
        {
            wait(clk.posedge_event());

            count1.write(++i);

            cout << sc_time_stamp()
                 << " Process 1: " << i << endl;
        }
    }

    void process2()
    {
        int j = 100;

        while (true)
        {
            wait(clk.posedge_event());

            count2.write(++j);

            cout << sc_time_stamp()
                 << " Process 2: " << j << endl;
        }
    }
};

int sc_main(int argc, char* argv[])
{
    testbench tb("tb");

    sc_start(60, SC_NS);

    return 0;
}
