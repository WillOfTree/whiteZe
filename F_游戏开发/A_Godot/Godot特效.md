# Godot特效使用方法

## 粒子系统

1. CPUParticles2D：老旧计算机使用
2. GPUParticles2D：更多的功能

参数说明

| 名称             | 说明                                                         |
| ---------------- | ------------------------------------------------------------ |
| Emitting         |                                                              |
| Amount           | 粒子数量                                                     |
| Amount Ratio     |                                                              |
| Sub Emitter      |                                                              |
| Process Material | 着色器设置                                                   |
| Texture          | 修改粒子的纹理                                               |
| Time             | 时间                                                         |
|                  | Lifetime：生命周期<br />One Shot<br />Preprocess<br />Speed Scale<br />Explosiveness<br />Randomness<br />Fixed FPS<br />Interpotate<br /> |
| Collision        |                                                              |
| Drawing          |                                                              |
| Trails           |                                                              |

着色器参数

New ShaderMaterial：着色器材质

New ParticleProcessMaterial：粒子处理材质

| 名称              | 说明                                                         |
| ----------------- | ------------------------------------------------------------ |
| Particle Flags    |                                                              |
| Spawn             |                                                              |
| Animated Velocity |                                                              |
| Accelerations     | 加速度                                                       |
|                   | Gravity：重力，控制粒子方向<br>Linear Accel<br />Radial Accel<br />Tangential Accel<br />Damping<br />Attractor Interaction |
| Display           | 显示                                                         |
|                   | Scale：<br />Scale Over Velocity<br />Color Curves<br />Hue Variation<br />Animation |
| Turbulence        |                                                              |
| Collision         |                                                              |
| Sub Emitter       |                                                              |
|                   |                                                              |



## 着色器

创建着色器，新建资源，shader / visualShader视觉着色器

将新建的资源着色器添加到 节点的canvasItem/ material属性中

## Animation