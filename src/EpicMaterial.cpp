#include "include/EpicMaterial.h"
#include "include/EpicException.h"
#include "include/EpicResourceManager.h"
#include "include/EpicRoot.h"
#include "assimp/include/material.h"
#include "FreeImage/FreeImage.h"

namespace epic {
	Material::Material(){
	}
	Material::~Material(){
	}
	void Material::InitMeshFromFile(const aiMaterial* material_from_file) {
		uint32 num_material_property = material_from_file->mNumProperties;
		
		for (uint32 j = 0; j < num_material_property; ++j) {
			const aiMaterialProperty* property = material_from_file->mProperties[j];
			String key(property->mKey.C_Str());
				
			if (key == "?mat.name") {
				aiString name;
				material_from_file->Get(AI_MATKEY_NAME,name);
				name_ = name.C_Str();
			}else if (key == "$mat.shadingm") {
				material_from_file->Get(AI_MATKEY_SHADING_MODEL, shading_model_);
			}else if (key == "$clr.emissive") {
				aiColor3D emissive;
				material_from_file->Get(AI_MATKEY_COLOR_EMISSIVE, emissive);
				color_emissive_ = Vector3(emissive.r, emissive.g, emissive.b);
			}else if (key == "$clr.diffuse") {
				aiColor4D diffuse;
				material_from_file->Get(AI_MATKEY_COLOR_DIFFUSE, diffuse);
				color_diffuse_ = Vector4(diffuse.r, diffuse.g, diffuse.b, diffuse.a);
			}else if (key == "$clr.specular") {
				aiColor3D specular;
				material_from_file->Get(AI_MATKEY_COLOR_SPECULAR, specular);
				color_specular_ = Vector3(specular.r, specular.g, specular.b);
			}else if (key == "$clr.ambient") {
				aiColor4D ambient;
				material_from_file->Get(AI_MATKEY_COLOR_AMBIENT, ambient);
				color_ambient_ = Vector4(ambient.r, ambient.g, ambient.b, ambient.a);
			}else if (key == "$mat.shininess") {
				material_from_file->Get(AI_MATKEY_SHININESS, shininess_);
			}else if (key == "$tex.file") {
				aiString path;
				material_from_file->GetTexture(static_cast<aiTextureType>(property->mSemantic), property->mIndex, &path);
				texture_path_ = path.C_Str();
				LoadTexture(texture_path_);
			}else {
				throw Exception("Material::InitMeshFromFile() can't find proper key type!");
			}
		}
			
		/*if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
			aiString path;
			if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS) {
				path;
			}
		}*/
	}
	void Material::LoadTexture(const String& file_name) {
		//image format
		FREE_IMAGE_FORMAT image_format = FIF_UNKNOWN;
		//pointer to the image, once loaded
		FIBITMAP *dib(0);
		//pointer to the image data
		BYTE* bits(0);
		//image width and height
		unsigned int width(0), height(0);
		//OpenGL's image ID to map to
		//GLuint gl_texID;

		//check the file signature and deduce its format
		image_format = FreeImage_GetFileType(file_name.c_str(), 0);
		//if still unknown, try to guess the file format from the file extension
		if(image_format == FIF_UNKNOWN) 
			image_format = FreeImage_GetFIFFromFilename(file_name.c_str());
		//if still unkown, return failure
		if(image_format == FIF_UNKNOWN)
			throw Exception("Material::LoadTexture() -> Unknown image format!");

		String full_path(Root::GetInstancePtr()->resource_manager()->resource_file_location());
		full_path += file_name;
		//check that the plugin has reading capabilities and load the file
		if(FreeImage_FIFSupportsReading(image_format))
			dib = FreeImage_Load(image_format, full_path.c_str());
		else 
			throw Exception("Material::LoadTexture() -> The image format didn't supported!");
		//if the image failed to load, return failure
		if(!dib)
			throw Exception("Material::LoadTexture() -> FreeImage_Load() failed!");

		//retrieve the image data
		bits = FreeImage_GetBits(dib);
		//get the image width and height
		width = FreeImage_GetWidth(dib);
		height = FreeImage_GetHeight(dib);
		//if this somehow one of these failed (they shouldn't), return failure
		if((bits == 0) || (width == 0) || (height == 0))
			throw Exception("Material::LoadTexture() -> Invalide image data!");
	}
} // epic