#pragma once

#include <GL/glew.h>

namespace Narradia
{
   // Model
#if 1
   enum class BufferTypes { Indices, Positions2D, Positions3D, Colors, Uvs, Normals };

   class RendBase {
     public:
      GLuint GenNewVAOId();
      GLuint GenNewBufId(BufferTypes buffer_type, GLuint vao_id);
      GLuint BufId(BufferTypes buffer_type, GLuint vao_id) const;
      void CleanupBase() const;

      static constexpr int kNumVerticesInRectangle = 4;
      inline static const auto kNumFloatsPerEntry = Map<BufferTypes, int>{
          {BufferTypes::Indices, 1}, {BufferTypes::Positions2D, 2}, {BufferTypes::Positions3D, 3},
          {BufferTypes::Colors, 4},  {BufferTypes::Uvs, 2},         {BufferTypes::Normals, 3}};

     private:
      Vec<GLuint> vao_ids_;
      Map<BufferTypes, Map<GLuint, GLuint>> vbo_ids_;
   };

   // Belonging ShaderProgram class
#if 1
   class ShaderProgram {
     public:
      void Cleanup();

      auto program_id() const {
         return program_id_;
      }

      void set_program_id(GLuint value) {
         program_id_ = value;
      }

     private:
      GLuint program_id_ = 0;
   };
#endif

// CameraGL using for tiles- and models rendering.
#if 1
   class CameraGL : public S<CameraGL> {
     public:
      auto persp_matrix() {
         return persp_matrix_;
      }

      void set_persp_matrix(glm::mat4 value) {
         persp_matrix_ = value;
      }

      auto view_matrix() {
         return view_matrix_;
      }

      void set_view_matrix(glm::mat4 value) {
         view_matrix_ = value;
      }

     private:
      glm::mat4 persp_matrix_;
      glm::mat4 view_matrix_;
   };
#endif

   // Shaders
#if 1
// 2D Images
#if 1
   inline static const GLchar *fragment_shader_source_2d_images =
       R"(
    #version 330 core
    precision mediump float;
    
    in vec4 ex_Color;
    in vec2 ex_TexCoord;
    uniform sampler2D TexUnit;

    out vec4 fragColor;

    void main()
    {
        vec4 texColor = texture(TexUnit, ex_TexCoord);
        fragColor = ex_Color*0.0 + texColor;
    }
)";

   inline static const GLchar *vertex_shader_source_2d_images =
       R"(
    #version 330 core

    layout (location = 0) in vec2 in_Position;
    layout (location = 1) in vec4 in_Color;
    layout (location = 2) in vec2 in_TexCoord;

    out vec4 ex_Color;
    out vec2 ex_TexCoord;

    void main()
    {
        gl_Position = vec4(in_Position.x, in_Position.y, 0.0, 1.0);
        ex_Color = in_Color;
        ex_TexCoord = in_TexCoord;
    }
)";
#endif

// 2D Solid Colors
#if 1
   inline static const GLchar *fragment_shader_source_2d_solid_colors =
       R"(
    #version 330 core
    precision mediump float;
    in vec4 ex_Color;

    out vec4 fragColor;

    void main() 
    {
        fragColor = ex_Color;
    }
)";

   inline static const GLchar *vertex_shader_source_2d_solid_colors =
       R"(
    #version 330 core

    layout (location = 0) in vec2 in_Position;
    layout (location = 1) in vec4 in_Color;

    out vec4 ex_Color;

    void main() 
    {
        gl_Position = vec4(in_Position.x, in_Position.y, 0.0, 1.0);
        ex_Color = in_Color;
    }
)";
#endif

// Models
#if 1
   inline static const GLchar *fragment_shader_source_models =
       R"(
    #version 330 core
    precision mediump float;

    vec3 light_direction = -vec3(0.0, -0.5, 4.5);
    vec3 light_ambient = vec3(0.65, 0.65, 0.65);
    vec3 light_color = vec3(0.6, 0.6, 0.5);

    in vec4 ex_Color;
    in vec2 ex_TexCoord;
    in vec3 ex_Normal;
    in float FogCoord;
    in vec3 FragPos;
    uniform sampler2D TexUnit;
    uniform float mAlpha;
    uniform vec3 mColorMod;
    uniform vec3 viewPos;
    uniform vec3 fogColor;
    uniform float noFog;
    uniform float noLighting;

    out vec4 fragColor;

    float nearPlane = 0.1;
    float farPlane = 165.0;

    float getFogFactor(float d, float nearPlane, float farPlane)
    {
        float FogMax = 1.0f * farPlane;
        float FogMin = 0.5f * farPlane;
        if (d>=FogMax) return 1.0f;
        if (d<=FogMin) return 0.0f;
        return 1.0f - (FogMax - d) / (FogMax - FogMin);
    }

    float getFogFactorAlpha(float d, float nearPlane, float farPlane)
    {
        float FogMax = 1.0f * farPlane;
        float FogMin = 0.7f * farPlane;
        if (d>=FogMax) return 1.0f;
        if (d<=FogMin) return 0.0f;
        return 1.0f - (FogMax - d) / (FogMax - FogMin);
    }

    void main()
    {
        vec4 color = vec4(ex_Color.rgb, texture(TexUnit, ex_TexCoord).a);

        if (color.a == 0.0)
            discard;

        vec3 result;
        vec3 mAmbient = light_ambient * texture(TexUnit, ex_TexCoord).rgb;

        if (noLighting == 0.0)
        {
            vec3 norm = normalize(ex_Normal);
            vec3 lightDir =normalize(-light_direction);
            float diff =  1.5*max(dot(norm, lightDir), 0.15);
            vec3 mDiffuse = light_color * diff * texture(TexUnit, ex_TexCoord).rgb;
            result = mAmbient + mDiffuse;
        }
        else
        {
            result = mAmbient;
        }

        fragColor = vec4(result*mAlpha, texture(TexUnit, ex_TexCoord).a);
        fragColor.r = fragColor.r*mColorMod.r;
        fragColor.g = fragColor.g*mColorMod.g;
        fragColor.b = fragColor.b*mColorMod.b;

        if (fogColor == vec3(1.0, 1.0, 1.0))
            return;

        if (noFog == 0.0)
        {
            float d = distance(viewPos, FragPos);
            float fogFactor = getFogFactor(d, nearPlane, farPlane);
            float alpha = getFogFactorAlpha(d, nearPlane, farPlane);
            fragColor = mix(fragColor, vec4(fogColor, 1.0f), fogFactor);
            if (fragColor.a == 1.0)
                fragColor.a = 1-alpha;
        }
    }
)";

   inline static const GLchar *vertex_shader_source_models =
       R"(
    #version 330 core

    layout (location = 0) in vec3 in_Position;
    layout (location = 1) in vec4 in_Color;
    layout (location = 2) in vec2 in_TexCoord;
    layout (location = 3) in vec3  in_Normal;

    out vec4 ex_Color;
    out vec2 ex_TexCoord;
    out vec3 ex_Normal;
    out vec3 FragPos;

    uniform mat4 projection;
    uniform mat4 view;
    uniform mat4 model;
    uniform mat4 modelNoTranslation;

    void main() 
    {
        vec4 newVertex;
        vec4 newNormal;
        newVertex.xyz = in_Position;
        newVertex.w = 1.0;
        newNormal.xyz = in_Normal;
        newNormal.w = 1.0;
        ex_Color = in_Color;
        gl_Position = projection * view * model * newVertex;
        ex_TexCoord = in_TexCoord;
        ex_Normal = (modelNoTranslation * newNormal).xyz;
        FragPos = vec3(model * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0));
    }
)";
#endif

// Tiles
#if 1
   inline static const GLchar *fragment_shader_source_tiles =
       R"(
    #version 330 core
    precision mediump float;

    vec3 light_direction = vec3(4.5, -3.0, -4.5);
    vec3 light_ambient = vec3(0.8, 0.8, 0.8);
    vec3 light_color = vec3(1.2, 0.7, 0.9);
    
    in vec4 ex_Color;
    in vec2 ex_TexCoord;
    in vec3 ex_Normal;
    in vec3 FragPos;
    uniform sampler2D TexUnit;
    uniform float mAlpha;
    uniform vec3 viewPos;
    uniform vec3 fogColor;

    out vec4 fragColor;

    float nearPlane = 0.1;
    float farPlane = 165.0;

    float getFogFactor(float d, float nearPlane, float farPlane)
    {
        float FogMax = 1.0f * farPlane;
        float FogMin = 0.5f * farPlane;
        if (d>=FogMax) return 1.0f;
        if (d<=FogMin) return 0.0f;
        return 1.0f - (FogMax - d) / (FogMax - FogMin);
    }

    float getFogFactorAlpha(float d, float nearPlane, float farPlane)
    {
        float FogMax = 1.0f * farPlane;
        float FogMin = 0.7f * farPlane;
        if (d>=FogMax) return 1.0f;
        if (d<=FogMin) return 0.0f;
        return 1.0f - (FogMax - d) / (FogMax - FogMin);
    }

    void main() 
    {
        vec4 color = vec4(ex_Color.rgb, texture(TexUnit, ex_TexCoord).a);

        if (color.a == 0.0)
            discard;

        vec3 mAmbient = light_ambient * texture(TexUnit, ex_TexCoord).rgb;
        vec3 norm = normalize(ex_Normal);
        vec3 lightDir = normalize(-light_direction);
        float diff = 3.5*max(dot(norm, lightDir), 0.15);
        vec3 mDiffuse = light_color * diff * texture(TexUnit, ex_TexCoord).rgb;
        vec3 result = mAmbient + mDiffuse;
        vec4 result2 = vec4(result.r*color.r, result.g*color.g, result.b*color.b, color.a);
        fragColor = result2;
        if (fogColor == vec3(1.0, 1.0, 1.0))
            return;
        float d = distance(viewPos, FragPos);
        float fogFactor = getFogFactor(d, nearPlane, farPlane);
        float alpha = getFogFactorAlpha(d, nearPlane, farPlane);
        fragColor = mix(fragColor, vec4(fogColor, 1.0f), fogFactor);
        fragColor.a = 1-alpha;
    }
)";

   inline static const GLchar *vertex_shader_source_tiles =
       R"(
    #version 330 core

    layout (location = 0) in vec3 in_Position;
    layout (location = 1) in vec4 in_Color;
    layout (location = 2) in vec2 in_TexCoord;
    layout (location = 3) in vec3  in_Normal;

    out vec4 ex_Color;
    out vec2 ex_TexCoord;
    out vec3  ex_Normal;
    out vec3 FragPos;

    uniform mat4 projection;
    uniform mat4 view;
    uniform mat4 model;

    void main() 
    {
        gl_Position = projection * view * vec4(in_Position, 1.0);
        ex_Color = in_Color;
        ex_TexCoord = in_TexCoord;
        ex_Normal = in_Normal;
        FragPos = vec3(model * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0));
    }
)";
#endif
#endif
#endif

// View
#if 1
   class RendBase;
   class ShaderProgramV;

   class RendBaseV {
     public:
      RendBaseV();
      void UseVAOBegin(GLuint vao_id) const;
      void UseVAOEnd() const;
      void SetIndicesData(GLuint indices_vbo_id, int num_vertices, const void *data) const;
      void SetData(
          GLuint vbo_id, int num_vertices, const void *data, BufferTypes buffer_type,
          int layout_location = -1) const;
      void UpdateIndicesData(GLuint indices_vbo_id, Vec<int> &indices) const;
      void UpdateData(
          GLuint vbo_id, Vec<float> &data, BufferTypes buffer_type, int layout_location) const;

      auto shader_program_view() {
         return shader_program_view_;
      }

      auto renderer_base() {
         return renderer_base_;
      }

     protected:
      GLuint GetUniformLocation(StringView var_name);
      void CleanupBase();

      SharedPtr<RendBase> renderer_base_;

     private:
      void SetArrayBufferData(
          GLuint vbo_id, int num_vertices, const void *data, int num_floats_per_entry,
          int layout_location = -1) const;
      void UpdateArrayBufferData(
          GLuint vbo_id, Vec<float> &data, int num_floats_per_entry, int layout_location) const;

      SharedPtr<ShaderProgramV> shader_program_view_;
   };

   // Belonging ShaderProgramV class
#if 1
   class ShaderProgram;

   class ShaderProgramV {
     public:
      ShaderProgramV();
      bool Create(const GLchar *vert_shader_src, const GLchar *frag_shader_src);

      auto shader_program() {
         return shader_program_;
      }

     private:
      GLuint CompileShader(const GLchar *shader_src, GLuint *shader, GLenum shader_type);

      SharedPtr<ShaderProgram> shader_program_;
   };
#endif
#endif
}
