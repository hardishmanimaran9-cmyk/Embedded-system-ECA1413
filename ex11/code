#include <systemc>
#include <iostream>
using namespace sc_core;
using namespace std;

// Product Producer
SC_MODULE(Producer)
{
    sc_fifo_out<int> out;

    SC_CTOR(Producer)
    {
        SC_THREAD(produce);
    }

    void produce()
    {
        for (int i = 1; i <= 5; i++)
        {
            cout << sc_time_stamp()
                 << " Product Created: " << i << endl;

            out.write(i);

            wait(2, SC_NS);
        }
    }
};

// Production Stage
SC_MODULE(Stage)
{
    sc_fifo_in<int> in;
    sc_fifo_out<int> out;

    const char* stage_name;

    SC_HAS_PROCESS(Stage);

    Stage(sc_module_name name, const char* s)
        : sc_module(name), stage_name(s)
    {
        SC_THREAD(process);
    }

    void process()
    {
        int product;

        while (true)
        {
            in.read(product);

            cout << sc_time_stamp()
                 << " " << stage_name
                 << " Processing Product: "
                 << product << endl;

            wait(3, SC_NS);

            out.write(product);
        }
    }
};

// Quality Inspection
SC_MODULE(Inspection)
{
    sc_fifo_in<int> in;

    SC_CTOR(Inspection)
    {
        SC_THREAD(inspect);
    }

    void inspect()
    {
        int product;

        while (true)
        {
            in.read(product);

            cout << sc_time_stamp()
                 << " Quality Inspection Passed: Product "
                 << product << endl;

            wait(1, SC_NS);
        }
    }
};

// Main System
int sc_main(int argc, char* argv[])
{
    sc_fifo<int> fifo1(5);
    sc_fifo<int> fifo2(5);
    sc_fifo<int> fifo3(5);

    Producer producer("Producer");

    Stage cutting("Cutting", "Cutting");
    Stage assembly("Assembly", "Assembly");

    Inspection inspection("Inspection");

    producer.out(fifo1);

    cutting.in(fifo1);
    cutting.out(fifo2);

    assembly.in(fifo2);
    assembly.out(fifo3);

    inspection.in(fifo3);

    cout << "\nPRODUCTION LINE STARTED\n\n";

    sc_start(100, SC_NS);

    cout << "\nPRODUCTION LINE COMPLETED\n";

    return 0;
}
