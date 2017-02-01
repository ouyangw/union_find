////////////////////////////////////////////////////////////////////////////////
// MIT License
// 
// Copyright (c) 2017 Wenjun Ouyang
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#ifndef UNION_FIND_HPP
#define UNION_FIND_HPP
#include <vector>
#include <cassert>

namespace union_find
{
template <typename Integer>
class UnionFind
{
public:
  explicit UnionFind(std::size_t size);
  Integer find_root(Integer i);
  void unite(Integer lhs, Integer rhs);
  std::size_t size() const;

private:
  struct Node_ {
    Integer parent;
    Integer rank;
    Node_(): parent(0), rank(0) {}
  };
  std::vector<Node_> m_vec;
};

////////////////////////////////////////////////////////////////////////////////

template <typename Integer>
UnionFind<Integer>::UnionFind(std::size_t size): m_vec(size)
{
  for (std::size_t i(0); i < size; ++i)
    m_vec[i].parent = i;
}

////////////////////////////////////////////////////////////////////////////////

template <typename Integer>
Integer UnionFind<Integer>::find_root(Integer i)
{
  assert(i < m_vec.size());
  if (m_vec[i].parent != m_vec[m_vec[i].parent].parent)
    m_vec[i].parent = find_root(m_vec[i].parent);
  return m_vec[i].parent;
}

////////////////////////////////////////////////////////////////////////////////

template <typename Integer>
void UnionFind<Integer>::unite(Integer lhs, Integer rhs)
{
  Integer lhs_root(find_root(lhs)), rhs_root(find_root(rhs));
  if (lhs_root != rhs_root) {
    if (m_vec[lhs_root].rank < m_vec[rhs_root].rank)
      m_vec[lhs_root].parent = rhs_root;
    else if (m_vec[lhs_root].rank > m_vec[rhs_root].rank)
      m_vec[rhs_root].parent = lhs_root;
    else {
      m_vec[rhs_root].parent = lhs_root;
      m_vec[lhs_root].rank += 1;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////

template <typename Integer>
std::size_t UnionFind<Integer>::size() const
{
  return m_vec.size();
}

} // namespace union_find

#endif
