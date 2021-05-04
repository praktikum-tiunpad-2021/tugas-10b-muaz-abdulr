#pragma once

#include <functional>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>

namespace strukdat
{

  template <typename VertexType>
  class graph
  {
    /**
   * @brief Tipe data dari adjacency list. (BOLEH DIUBAH)
   *
   * @note
   * Misal:
   *
   * adj_list_type adj_list =
   *
   * | map key  |             list_type
   * | - - - -  | - - - - - - - - - - - - - - - - -
   * | vertex_1 | vertex_2, vertex_5, vertex_4, ...
   * | vertex_2 | vertex_1, vertex_3
   * |   ...    |           ...
   *
   * maka,
   *
   * adj_list[vertex_2]; // { vertex_1, vertex_3 }
   */
    using list_type = std::unordered_set<VertexType>;
    using adj_list_type = std::unordered_map<VertexType, list_type>;

  public:
    /**
   * @brief Default constructor.
   *
   * @constructor
   */
    graph() {}

    /**
   * @brief Menambahkan vertex baru pada graph
   *
   * @param val nilai dari vertex yang akan ditambahkan
   */
    void add_vertex(const VertexType &val)
    {
      // Contoh implementasi. (BOLEH DIUBAH)
      // inisialisasi _adj_list[val] dengan list kosong
      _adj_list.insert(std::make_pair(val, list_type()));
    }

    void remove_vertex(const VertexType &val)
    {
      _adj_list.erase(val);
    }

    /**
   * @brief Menambahkan edge baru dari 2 vertex
   *
   * @param val1 nilai vertex 1
   * @param val2 nilai vertex 2
   */
    void add_edge(const VertexType &val1, const VertexType val2)
    {
      list_type adj1 = _adj_list[val1];
      list_type adj2 = _adj_list[val2];
      adj1.insert(val2);
      adj2.insert(val1);
    }

    /**
   * @brief Menghapus vertex baru pada graph
   *
   * @param val nilai dari vertex yang akan dihapus
   */
    void remove_edge(const VertexType &val1, const VertexType &val2)
    {
      _adj_list.at(val1).erase(val2);
      _adj_list.at(val2).erase(val1);
    }

    /**
   * @brief Mengembalikan ordo dari graph.
   *
   * @note
   * Ordo graph adalah jumlah node pada graph
   *
   * @return jumlah node pada graph
   */
    size_t order() const
    {
      return _adj_list.size();
    }

    /**
   * @brief Cek apakah 2 vertex bertetangga satu sama lain.
   *
   * @param val1 nilai vertex 1
   * @param val2 nilai vertex 2
   *
   * @return vertex-vertex saling bertetangga
   */
    bool is_edge(const VertexType &val1, const VertexType &val2) const
    {
      auto p1 = _adj_list.at(val1).find(val2);
      auto p2 = _adj_list.at(val2).find(val1);
      if (p1 != _adj_list.at(val1).end() && p2 != _adj_list.at(val2).end())
      {
        return true;
      }
      return false;
    }

    /**
   * @brief Melakukan BFS traversal pada graph
   *
   * @param root vertex awal
   * @param func fungsi yang akan dieksekusi pada setiap vertex
   */
    void bfs(const VertexType &root,
             std::function<void(const VertexType &)> func) const
    {
      std::unordered_map<VertexType, bool> m;
      std::queue<VertexType> q;
      VertexType node = root;
      for (auto it = _adj_list.begin(); it != _adj_list.end(); it++)
      {
        m.insert(std::make_pair(it->first, 0));
      }
      q.push(node);
      m[node] = true;
      while (!q.empty())
      {
        node = q.front();
        func(node);
        q.pop();
        for (auto i = _adj_list.at(node).begin(); i != _adj_list.at(node).end(); i++)
        {
          if (!m[*i])
          {
            m[*i] = true;
            q.push(*i);
          }
        }
      }
    }

    /**
   * @brief Melakukan BFS traversal pada graph
   *
   * @param root vertex awal
   * @param func fungsi yang akan dieksekusi pada setiap vertex
   */
    void dfs(const VertexType &root,
             std::function<void(const VertexType &)> func) const
    {
      std::unordered_map<VertexType, bool> m;
      std::stack<VertexType> s;
      VertexType node = root;
      for (auto it = _adj_list.begin(); it != _adj_list.end(); it++)
      {
        m.insert(std::make_pair(it->first, 0));
      }
      s.push(node);
      while (!s.empty())
      {
        if (!m[node])
        {
          func(node);
        }
        auto i = _adj_list.at(node).begin();
        for (; i != _adj_list.at(node).end(); i++)
        {
          if (!m[*i])
          {
            node = *i;
            s.push(node);
            break;
          }
        }
        if (i == _adj_list.at(node).end())
        {
          node = s.top();
          s.pop();
        }
      }
    }

  private:
    /**
   * @brief Adjacency list dari graph
   *
   * @private
   */
    adj_list_type _adj_list;
  };

} // namespace strukdat