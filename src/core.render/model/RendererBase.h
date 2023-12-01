#pragma once
#include "BufferTypes.h"

namespace Narradia {
    class ShaderProgram;

    class RendererBase {
      public:
        constexpr static int kNumVerticesInRectangle = 4;
        constexpr static int kNumFloatsPerIndex = 1;
        constexpr static int kNumFloatsPerPosition2D = 2;
        constexpr static int kNumFloatsPerPosition3D = 3;
        constexpr static int kNumFloatsPerColor = 4;
        constexpr static int kNumFloatsPerUv = 2;
        constexpr static int kNumFloatsPerNormal = 3;

        GLuint GenerateNewVertexArrayId();

        GLuint GenerateNewBufferId(BufferTypes buffer_type, GLuint vao_id);

        GLuint GetBufferId(BufferTypes buffer_type, GLuint vao_id) const;

      protected:
        void CleanupBase() const;

      private:
        std::vector<GLuint> vao_ids_;
        std::map<BufferTypes, std::map<GLuint, GLuint>> vbo_ids_;
    };
}
