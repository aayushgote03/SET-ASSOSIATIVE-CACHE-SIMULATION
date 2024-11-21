#include <iostream>
#include <bits/stdc++.h>
#include <utility> 
#include <unordered_map>
#include <chrono>
#include <random>
#include <cmath>
#include <vector>
#include <bitset>
#include <thread>

using namespace std;

long long hit_count = 0; //counter for hits
long long miss_count = 0; // counter for misses

vector<vector<pair<bitset<2>, bitset<28>>>> cache(    //cache declaration : 64 sets and 8 lines in each set and each line : 2bits for state and 28 bits for tag
    64, vector<pair<bitset<2>, bitset<28>>>(
            8, {bitset<2>("00"), bitset<28>(0)}));  

//function to generate a random 40 bit adddress

double generateRandomDecimal() {  // Function to generate a random decimal number between 0 and 1
    random_device rd;  // Obtain a random number from hardware
    mt19937 generator(rd());  // Seed the generator
    uniform_real_distribution<double> distribution(0.0, 1.0);  // Define the range [0.0, 1.0]
    return distribution(generator);  // Generate and return a random number
}

int generateRandomNumber() { // function to generate a random decimal number from 0 to 7 required for the random replacement algorithm
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, 7);
    return distrib(gen);
}


void read_cache(bitset<28> tag, bitset<6> set_no) {  //cache to handle read requests
    int set_no_index = static_cast<int>(set_no.to_ulong()); // convert the set number format to binary;
    if(set_no_index >= 64) {
        cout << "set_no not present in cache";
        return; //set no. excedding the upper limit
    }

    for(int i = 0; i < 8; i++) { 
        int curr_line_no = i; //current line no cache is accessing
        bitset<28> line_tag_bit = cache[set_no_index][curr_line_no].second; // tag bit of the current line
        bitset<2> line_state_bit = cache[set_no_index][curr_line_no].first; // state bit of the current line

        if(line_tag_bit == tag && line_state_bit == bitset<2>("01")) { // check for hit case : 01 represents hit
            hit_count++; //increment hit count
            return;
        } 
    }

    //if no hit occurs then the request is a miss then find a block with invalid bit or the block which is empty 
    //then the below loop will get implemented 

    for(int i = 0; i < 8; i++) { // check if we find a line which is empty
        int curr_line_no = i; //current line no cache is accessing
        bitset<2> line_state_bit = cache[set_no_index][curr_line_no].first; // state bit of the current line

        if(line_state_bit == bitset<2>("00")) { // check for a line with invalid
            cache[set_no_index][curr_line_no].first = bitset<2>("01"); // set the state bit of the line to 
            cache[set_no_index][curr_line_no].second = tag; //replace the tag bits 
            miss_count++; // increment miss count;
            return;
        } 
    }

    // if no empty line is found then any one of the filled line must be emptied for index 0 - 8 to make place for the requested data
    // then the below statements will be executed

    //random replacement algorithm

    int victim_ind = generateRandomNumber(); // get a line no index to be replaced;

    cache[set_no_index][victim_ind].first = bitset<2>("01"); // set the state bit of the line to 
    cache[set_no_index][victim_ind].second = tag; //replace the tag bits 
    miss_count++; // increment miss count

    //end

    return;
}

void write_through_cache(bitset<28> tag, bitset<6> set_no) { //cache to handle the write requests
    int set_no_index = static_cast<int>(set_no.to_ulong()); // convert set_no format to binary
    for(int i = 0; i < 8; i++) { 
        int curr_line_no = i; //current line no cache is accessing
        bitset<28> line_tag_bit = cache[set_no_index][curr_line_no].second; // tag bit of the current line
        bitset<2> line_state_bit = cache[set_no_index][curr_line_no].first; // state bit of the current line

        if(line_tag_bit == tag && line_state_bit == bitset<2>("01")) { // check for hit case : 01 represents hit
            hit_count++; //increment hit count
            return;
        } 
    }
    miss_count++;
    return;
}

uint64_t generateNormalDistributionAddress(double mean, double stddev) {
    random_device rd;
    mt19937_64 gen(rd());
    normal_distribution<double> dist(mean, stddev);

    double address = dist(gen);
    
    address = max(0.0, min(address, static_cast<double>((1ULL << 40) - 1)));

    return static_cast<uint64_t>(address);
}

int main() {

    int duration; 
    cout << "Enter the duration for the loop to run (in seconds): ";
    cin >> duration; // enter the time in seconds for which the cache will implement

    auto start = chrono::high_resolution_clock::now();

    double mean = (1ULL << 10);
    double std_dev = (1ULL << 22); 


    cout << "cache implementation begin: **************************************" << endl;

    while(1) {   //iterate for every random address generated and pass it through the cache
        //int rand_Address = get40bitaddress(); //get a random 40 bit address
        auto now = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::seconds>(now - start);

        uint64_t randomAddress = generateNormalDistributionAddress(mean,std_dev);

        uint64_t tag = (randomAddress >> 12) & ((1ULL << 28) - 1); // our ttag is 28 bit long => 40 - 6(set_no) -6(block-offset)
        uint64_t set_no = (randomAddress >> 6) & ((1ULL << 6) - 1); // 6 bit long set no. since we have 64 sets in cache
        

        if (elapsed.count() >= duration) {
            break; // Exit the loop after the specified time
        }

        double read_or_write_decide = generateRandomDecimal(); //to simulate read or write instruction produced by the cpu;

        if(read_or_write_decide < 0.5) { 
            read_cache(bitset<28>(tag), bitset<6>(set_no));//implement reading cache;
        }
        else {
            write_through_cache(bitset<28>(tag), bitset<6>(set_no));//implement write through cache
        }

        // Optional: Do some work or just sleep for a short time to prevent CPU overuse
    }

    cout << "total no of acceess: " << hit_count + miss_count << endl;
    cout << "no of hits:"  << hit_count << endl;
    cout << "no of misses:"  << miss_count << endl;
    double no_of_access = hit_count + miss_count;
    double hit_ratio = (hit_count / no_of_access) * 100;
    cout << "hit ratio: " << hit_ratio << endl;

    return 0;
}