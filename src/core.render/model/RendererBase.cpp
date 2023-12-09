#include "RendererBase.h"
#include "core.render/model/ShaderProgram.h"

namespace Narradia {
    /**
     Generate id for a new vertex array object (VAO).
    */
    GLuint RendererBase::GenerateNewVertexArrayId() {
        GLuint new_vao_id;
        glGenVertexArrays(1, &new_vao_id);
        vao_ids_.push_back(new_vao_id);

        return new_vao_id;
    }

    /**
     * Generate id for a new vertex buffer object (VBO.
     */
    GLuint RendererBase::GenerateNewBufferId(BufferTypes buffer_type, GLuint vao_id) {
        GLuint new_buffer_id;
        glGenBuffers(1, &new_buffer_id);
        vbo_ids_[buffer_type][vao_id] = new_buffer_id;

        return new_buffer_id;
    }

    /**
     * Obtains a VBO-id for a specific buffer type and VAO-id.
     */
    GLuint RendererBase::GetBufferId(BufferTypes buffer_type, GLuint vao_id) const {
        return vbo_ids_.at(buffer_type).at(vao_id);
    }

    /**
     * Cleanup VBOs and VAO at class disposal.
     */
    void RendererBase::CleanupBase() const {
        for (auto &buffer_type : vbo_ids_) {
            for (auto &buffer_entry : buffer_type.second) {
                glDeleteBuffers(1, &buffer_entry.second);
            }
        }

        for (auto vao_id : vao_ids_) {
            glDeleteVertexArrays(1, &vao_id);
        }
    }
}
