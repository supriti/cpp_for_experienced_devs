    #include<iostream>
    #include<thread>
    #include<vector>
    #include<atomic>
    #include<mutex>

    using namespace std;

    mutex cout_mtx;
    void hello(atomic<int>& val) {
        int curren_val = val++;
        thread::id current_thread_id = this_thread::get_id();
        lock_guard<mutex> lock(cout_mtx);

        cout << endl << "Hello from thread"  << current_thread_id << ":" << val <<  " " <<  endl;
    }

    int main(){
        atomic<int> val = 0;
        vector<thread> threads;

        for(int i = 0;i < 5; i++) {
            threads.emplace_back(hello, ref(val));
        }

        for(thread& t:threads){
            if(t.joinable()){
                t.join();
            }
        }

        cout << "All threads finished" << endl;
        return 0;
    }