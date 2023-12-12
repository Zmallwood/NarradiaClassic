#pragma once
namespace Narradia
{
    class CameraGL : public Singleton<CameraGL> {
      public:
        auto perspective_matrix() {
            return perspective_matrix_;
        }

        void set_perspective_matrix(glm::mat4 value) {
            perspective_matrix_ = value;
        }

        auto view_matrix() {
            return view_matrix_;
        }

        void set_view_matrix(glm::mat4 value) {
            view_matrix_ = value;
        }
      private:
        glm::mat4 perspective_matrix_;
        glm::mat4 view_matrix_;
    };
}
