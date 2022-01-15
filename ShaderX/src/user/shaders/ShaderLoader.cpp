#include "pch.h"
#include "ShaderLoader.h"
#include <shobjidl.h> 

std::wstring ShaderLoader::current_path = L"";


std::wstring ShaderLoader::open()
{
    std::wstring fileName;
	IFileOpenDialog *pFileOpen;
    HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
						  IID_IFileOpenDialog, reinterpret_cast<void **>(&pFileOpen));
    if (SUCCEEDED(hr)) {
           // Show the Open dialog box.
        hr = pFileOpen->Show(NULL);

        // Get the file name from the dialog box.
        if (SUCCEEDED(hr)) {
            IShellItem *pItem;
            hr = pFileOpen->GetResult(&pItem);
            if (SUCCEEDED(hr)) {
                wchar_t *pszFilePath = 0;

                hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                std::cout << *pszFilePath << std::endl;

                // Display the file name to the user.
                if (SUCCEEDED(hr)) {
                    //MessageBox(NULL, pszFilePath, L"File Path", MB_OK);
                    std::wstringstream ss;
                    ss << pszFilePath;
                    fileName = ss.str();
                    CoTaskMemFree(static_cast<void *>(pszFilePath));
                }
                pItem->Release();
            }
        }
        pFileOpen->Release();
    }
    current_path = fileName;
    return fileName;
}

std::string ShaderLoader::load(std::string path)
{
    printf("from ShaderLoader::load, path = %s\n", path.c_str());
    std::string code;
    std::ifstream shader_file;
    shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        shader_file.open(path);

        std::stringstream shader_stream;
        shader_stream << shader_file.rdbuf();
        shader_file.close();
        code = shader_stream.str();
    }
    catch (std::ifstream::failure &e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }
    return code;
}

void ShaderLoader::save(std::string &source)
{
    std::ofstream file;
    file.open(current_path);
    file << source;
    file.close();
}

void ShaderLoader::save_as(std::string &source)
{
    std::wstring fileName;
	IFileSaveDialog *pFileSave;
    HRESULT hr = CoCreateInstance(CLSID_FileSaveDialog, NULL, CLSCTX_ALL,
						  IID_IFileSaveDialog, reinterpret_cast<void **>(&pFileSave));
    if (SUCCEEDED(hr)) {
           // Show the Open dialog box.
        hr = pFileSave->Show(NULL);

        // Get the file name from the dialog box.
        if (SUCCEEDED(hr)) {
            IShellItem *pItem;
            hr = pFileSave->GetResult(&pItem);
            if (SUCCEEDED(hr)) {
                wchar_t *pszFilePath = 0;

                hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
                std::cout << *pszFilePath << std::endl;

                // Display the file name to the user.
                if (SUCCEEDED(hr)) {
                    //MessageBox(NULL, pszFilePath, L"File Path", MB_OK);
                    std::wstringstream ss;
                    ss << pszFilePath;
                    fileName = ss.str();
                    CoTaskMemFree(static_cast<void *>(pszFilePath));
                }
                pItem->Release();
            }
        }
        pFileSave->Release();
    }
    current_path = fileName;
    save(source);
}
