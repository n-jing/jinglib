#include <cmath>
#include <fstream>
#include <array>
#include <tuple>
#include <vector>

namespace Jing
{
  template<typename T>
  struct Vertex : public std::array<T, 3>
  {
    Vertex(T a=0, T b=0, T c=0) : std::array<T, 3>{a, b, c} { }
  };

  template<typename T>
  Vertex<T> operator+(const Vertex<T> &a, const Vertex<T> &b)
  {
    return {a[0]+b[0], a[1]+b[1], a[2]+b[2]};
  }

  template<typename T>
  Vertex<T> operator-(const Vertex<T> &a, const Vertex<T> &b)
  {
    return {a[0]-b[0], a[1]-b[1], a[2]-b[2]};
  }

  template<typename T>
  T operator*(const Vertex<T> &a, const Vertex<T> &b)
  {
    return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
  }

  template<typename T>
  Vertex<T> operator^(const Vertex<T> &a, const Vertex<T> &b)
  {
    return {a[1]*b[2] - a[2]*b[1],
        a[2]*b[0] - a[0]*b[2],
        a[0]*b[1] - a[1]*b[0]};
  }

  template<typename T>
  std::tuple<bool, std::vector<Vertex<T>>, std::vector<std::array<int, 3>>> read_model(
    const char *path)
  {
    FILE *model_file = fopen(path, "r");
    if (!model_file || std::string(path).find(".obj") == std::string::npos)
    {
      return std::make_tuple<bool,std::vector<Vertex<T>>, std::vector<std::array<int, 3>>>(
        false, {}, {});
    }
    char line[512];
    std::vector<Vertex<T>> model_vertices;
    std::vector<std::array<int, 3>> model_faces;
    while (!feof(model_file))
    {
      fscanf(model_file, "%[^\n]%*[\n]", line);
      if (line[0] == 'v' && line[1] == ' ')
      {
        Vertex<T> v;
        sscanf(line, "%*c%lf%lf%lf", &v[0], &v[1], &v[2]);
        model_vertices.push_back(move(v));
      }
      else if (line[0] == 'f' && line[1] == ' ')
      {
        std::array<int, 3> f;
        if (std::string(line).find("/") != std::string::npos)
          sscanf(line, "%*c%d%*s%d%*s%d", &f[0], &f[1], &f[2]);
        else
          sscanf(line, "%*c%d%d%d", &f[0], &f[1], &f[2]);
        model_faces.emplace_back(std::array<int, 3>{f[0]-1, f[1]-1, f[2]-1});
      }
    }

    return std::make_tuple(true, model_vertices, model_faces);
  }
}


#ifdef CALC_ELE_SIDE_LENGTH
using FLOAT_TYPE = double;
int main (int argc, char *argv[])
{
  if (argc != 3)
  {
    printf("usage: exe obj_model_path element_number. \n");
    return -1;
  }
  bool file_exist = false;
  std::vector<Vertex<FLOAT_TYPE>> model_vertices;
  std::vector<std::array<int, 3>> model_faces;
  std::tie(file_exist, model_vertices, model_faces) = read_model<FLOAT_TYPE>(argv[1]);
  if (!file_exist)
  {
    printf("0\n");
    return -1;
  }

  double volume = 0;
  const int face_num = model_faces.size();
  for (int f = 0; f < face_num; ++f)
  {
    const auto &face = model_faces[f];
    const Vertex<FLOAT_TYPE> &a = model_vertices[face[0]];
    const Vertex<FLOAT_TYPE> &b = model_vertices[face[1]];
    const Vertex<FLOAT_TYPE> &c = model_vertices[face[2]];
    volume += (a ^ b) * c / 6;
  }
  const int element_num = atoi(argv[2]);
  double element_volume = fabs(volume) / element_num;
  printf("%lf\n", pow(element_volume, 1.0 / 3.0));
  return 0;
}
#endif 
