#include "ModelBank.h"
#include "core.assets.model_creation/model/ModelCreator.h"

namespace Narradia {
    ModelBank::ModelBank()
        : models_(std::make_shared<std::map<std::string_view, std::shared_ptr<Model>>>()) {
        LoadModels();
    }

    void ModelBank::LoadModels() {
        using iterator = std ::filesystem::recursive_directory_iterator;
        auto abs_all_models_path = std::string(SDL_GetBasePath()) + kRelModelsPath.data();
        for (const auto &file_path : iterator(abs_all_models_path)) {
            auto path_str = file_path.path().string();
            auto extension_pos = path_str.find_last_of('.') + 1;
            auto file_extension = path_str.substr(extension_pos);
            if (file_extension != "dae")
                continue;
            auto loaded_model = LoadSingleModel(path_str);
            auto image_name_start = path_str.find_last_of('/') + 1;
            auto image_name_with_ext = path_str.substr(image_name_start);
            auto image_name_ext_pos = image_name_with_ext.find_last_of('.');
            auto file_name_no_ext = image_name_with_ext.substr(0, image_name_ext_pos);
            models_->insert({file_name_no_ext, loaded_model});
        }
    }

    std::shared_ptr<Model> ModelBank::LoadSingleModel(std::string_view path_str) {
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(path_str.data(), 0);
        return ModelCreator::Get()->CreateModel(scene);
    }

    std::shared_ptr<Model> ModelBank::GetModel(std::string_view model_name) {
        return models_->at(model_name);
    }
}
