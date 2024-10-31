#pragma once

#shader vertex
 #version 410 core

     layout(location = 0) in vec4 position;
     layout(location = 1) in vec2 position;

     out vec2 v_texCoord;

     void main()
     {
         gl_position = position;
         v_texCoord = texCoord;
     };

#shader fragment
 #version 410 core

     layout(location = 0) in vec4 position;

     in vec2 v_texCoord;

     uniform vec4 u_color;
     uniform sampler2D u_texture;

     void main()
     {
         vec4 texColor = texture(u_texture, v_texCoord);
         color = texColor;
     };