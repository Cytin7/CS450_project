#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string>
#include <vector>

int save_NLp(int N, int L, float p)
{
    std::ofstream outFile("config");
    if (!outFile.is_open())
    {
        std::cerr << "Unable to open the file." << std::endl;
        return -1;
    }
    outFile << N << "," << L << "," << p << std::endl;
    outFile.close();
    return 0;
}

// Define the data stucture of a linked list
class Node
{
private:
    int pos;
    float chance;
    Node *next;

public:
    Node(float fail_rate) : pos(0), chance(fail_rate), next(nullptr){};

    bool freeze() { return ((double)rand() / RAND_MAX < chance); };
    void move() { ++pos; };
    void send_back() { pos = 0; };

    friend class LinkedList;
};

class LinkedList
{
private:
    Node *head;
    Node *tail;
    int N;
    int L;

    // Add the node to the end of list
    void addNode(float fail_rate)
    {
        // if (this->tail == nullptr)
        //     std::cerr << "Error Adding Node: tail is nullptr" << std::endl;
        Node *newNode = new Node(fail_rate);
        this->tail->next = newNode;
        this->tail = newNode;
    };

    void round()
    {
        Node *prev = this->head;
        Node *curr = prev->next;

        int count = 0;
        for (int i = 0; i < this->N; ++i)
        {
            // if (curr == nullptr)
            //     std::cerr << "Error simulating: curr is nullptr" << std::endl;
            curr->move();
            if (count < this->L and curr->freeze())
            {
                ++count;
                curr->send_back();
                if (curr == this->tail)
                    this->tail = prev;
                prev->next = curr->next;
                curr->next = nullptr;
                this->tail->next = curr;
                this->tail = curr;
            }
            else
                prev = curr;
            curr = prev->next;
        }
    };

    template <typename T>
    int vec2file(int scale, std::vector<T> out_vec, const std::string &file_name = "data")
    {
        std::ofstream outputFile(file_name, std::ios::out | std::ios::binary);
        if (!outputFile.is_open())
        {
            std::cerr << "Error opening the file: " << file_name << std::endl;
            return -1;
        }
        for (int j = 0; j < out_vec.size(); ++j)
        {
            double tmp = ((double)out_vec[j]) / scale;
            outputFile.write(reinterpret_cast<const char *>(&tmp), sizeof(double));
        }
        outputFile.close();
        return 0;
    };

public:
    // Initialization
    LinkedList(int N, int L, float fail_rate) : N(N), L(L)
    {
        Node *dumb = new Node(0.0);
        this->head = dumb;
        this->tail = dumb;
        for (int i = 0; i < this->N; ++i)
            addNode(fail_rate);
    };

    void restart()
    {
        Node *current = this->head->next;
        while (!(current == nullptr))
        {
            current->send_back();
            current = current->next;
        }
    };

    void run(int K = 1, int disp_num = 100)
    {
        for (int i = 0; i < K; ++i)
        {
            if (i % disp_num == 0)
                std::cout << "Runnning Game... Round #" << i << std::endl;
            this->round();
        }
    };

    void display()
    {
        Node *curr = this->head->next;
        int count = 0;
        while (!(curr == nullptr))
        {
            std::cout << ++count << "\t" << curr->pos << std::endl;
            curr = curr->next;
        }
    };

    int gen_file(int batch = 5, int run_steps = 5000, int test_steps = 100, const std::string &file_name = "data")
    {
        std::vector<int> out_vec(this->head->pos);
        for (int i = 0; i < batch; ++i)
        {
            std::cout << "Running Batch #" << i << std::endl;
            this->restart();
            this->run(run_steps);
            for (int k = 0; k < test_steps; ++k)
            {
                this->round();
                for (int j = out_vec.size(); j < head->next->pos + 1; ++j)
                    out_vec.push_back(0);
                Node *current = head;
                while (current)
                {
                    ++out_vec[current->pos];
                    current = current->next;
                }
            }
        }
        return vec2file(batch * run_steps * N, out_vec, file_name);
    }
};

int main()
{
    srand(time(nullptr)); // randomize
    int N = 10;
    int L = 1;
    float p = 0.05;
    save_NLp(N, L, p);
    LinkedList game(N, L, p);
    game.gen_file();

    return 0;
}