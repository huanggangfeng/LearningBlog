#include <atomic>
#include <thread>
#include <iostream>
#include <vector>

std::atomic<int> cnt = {0};

void f() {
   for (size_t i = 0; i < 1000; i++) {
      cnt.fetch_add(1, std::memory_order_relaxed);
   }
}

int main(int argc, char const *argv[]) {
   std::vector<std::thread> v;
   for (size_t i = 0; i < 10; i++) {
      v.emplace_back(f);
   }

   for (auto &t : v)
   {
      t.join();
   }

   std::cout << "Final value:" << cnt << '\n';
   return 0;
}
