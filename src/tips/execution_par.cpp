#include <iostream>

#include <execution>
#include <vector>

int main() {
  std::vector<int> v(10, 0);

  //给vector赋值随机
  std::for_each(std::execution::par, v.begin(), v.end(), [](int& i) {
      i = rand();
  });

  for(auto d : v){
      std::cout<<d<<" ";
  }

  std::cout<<"\n=====================\n";

  // 排序
  std::sort(std::execution::par, v.begin(), v.end());
  for(auto d : v){
      std::cout<<d<<" ";
  }

  std::cout<<"\n=====================\n";

  //用并行版的transform
  std::vector<int> result(v.size());
  std::transform(std::execution::par, v.begin(), v.end(), result.begin(), [](int i) {
      return i * 2;
  });

  for(auto d : result){
      std::cout<<d<<" ";
  }

  return 0;
}