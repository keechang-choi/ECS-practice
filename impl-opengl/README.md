# ECS OpenGL implementation

reference: https://austinmorlan.com/posts/entity_component_system/


## step-0
- installation
## step-1
- base structure for ECS
- simple static cude rendering
- ![image](https://user-images.githubusercontent.com/49244613/209937087-93ef027a-0553-47ba-8f2f-d67be959114f.png)
## step-2
- projection and view matrix
- 
$$
perspective \; projecton \\
\left[
\begin{matrix}
    \frac{1}{(\frac{w}{h})*tan(\frac{\theta}{2})} & 0 & 0 & 0 \\
    0 & \frac{1}{tan(\frac{\theta}{2})} & 0 & 0 \\
    0 & 0 & -\frac{f+n}{f-n} & -\frac{2fn}{f-n} \\
    0 & 0 & -1 & 0 \\ 
\end{matrix}
\right]
$$

## step-3
- gravity and rigid body component
- phsics system
- fix: normal vector transform matrix
- rotation velocity
- |                                       |                                       |
  |:-------------------------------------:|:-------------------------------------:|
  | ![image](https://user-images.githubusercontent.com/49244613/229608395-9a9e8178-fe59-4bb7-8f33-3e81a6230e78.png) | ![image](https://user-images.githubusercontent.com/49244613/229608133-73372e58-5d15-4a61-af90-c58024ca199f.png) |
  | ![image](https://user-images.githubusercontent.com/49244613/229608157-f690f228-acbe-49fa-bcb7-18adf342c2d2.png) | ![image](https://user-images.githubusercontent.com/49244613/229608179-37075c24-6c79-4275-afe5-cedf18d43afc.png) |

## step-4
- Demo
  - ![ECS-demo](https://user-images.githubusercontent.com/49244613/230783393-f6a595c1-9f83-4029-8032-641fb0c46c5a.gif)
- verification
```
valgrind --tool=cachegrind ./ECS-PRACTICE-CKC
```
- D1 cache miss comparison
  |            ECS                        |              OOP                      |
  |:-------------------------------------:|:-------------------------------------:|
  | ![image](https://user-images.githubusercontent.com/49244613/230783353-cb029e6f-a592-4abf-b3f2-517087bae443.png) | ![image](https://user-images.githubusercontent.com/49244613/230783359-726e06a4-d0d5-4e41-a663-be9d4b95b3c6.png) |
