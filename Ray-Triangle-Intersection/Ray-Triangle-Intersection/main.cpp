#include "Scene.hpp"
#include "Sphere.hpp"
#include "Triangle.hpp"
#include "Light.hpp"
#include "Renderer.hpp"

// In the main function of the program, we create the scene (create objects and
// lights) as well as set the options for the render (image width and height,
// maximum recursion depth, field-of-view, etc.). We then call the render
// function().
int main() {
  // 定义场景的参数，添加物体（球体或三角形）到场景中，
  // 并设置其材质，然后将光源添加到场景中。
  Scene scene(1280, 960);

  auto sph1 = std::make_unique<Sphere>(Vector3f(-1, 0, -12), 2);
  sph1->materialType = DIFFUSE_AND_GLOSSY;
  sph1->diffuseColor = Vector3f(0.6, 0.7, 0.8);

  auto sph2 = std::make_unique<Sphere>(Vector3f(0.5, -0.5, -8), 1.5);
  sph2->ior = 1.5;
  sph2->materialType = REFLECTION_AND_REFRACTION;

  scene.Add(std::move(sph1));
  scene.Add(std::move(sph2));

  Vector3f verts[4] = {{-5, -3, -6}, {5, -3, -6}, {5, -3, -16}, {-5, -3, -16}};
  uint32_t vertIndex[6] = {0, 1, 3, 1, 2, 3};
  Vector2f st[4] = {{0, 0}, {1, 0}, {1, 1}, {0, 1}};
  auto mesh = std::make_unique<MeshTriangle>(verts, vertIndex, 2, st);
  mesh->materialType = DIFFUSE_AND_GLOSSY;

  scene.Add(std::move(mesh));
  scene.Add(std::make_unique<Light>(Vector3f(-20, 70, 20), 0.5));
  scene.Add(std::make_unique<Light>(Vector3f(30, 50, -12), 0.5));

  Renderer r;
  // 调用 Render(scene) 函数。在遍历所有像素的循环里，
  // 生成对应的光线并将返回的颜色保存在帧缓冲区（framebuffer）中。
  // 在渲染过程结束后，帧缓冲区中的信息将被保存为图像。
  r.Render(scene);

  return 0;
}
