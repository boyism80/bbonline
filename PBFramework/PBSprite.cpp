#include "PBSprite.h"
using namespace PB::Windows;

image::image(Pivot pivot)
{
    this->_image                        = NULL;
    this->_stream                       = NULL;
    this->_handle                       = NULL;
    this->_pivot                        = pivot;
}

image::image(const wchar_t* filename, Pivot pivot) : image(pivot)
{
    if(this->load(filename) == false)
        throw std::exception("PBImage(filename)");
}

image::image(const char * bytes, int size, Pivot pivot) : image(pivot)
{
    if(this->load(bytes, size) == false)
        throw std::exception("PBImage(bytes, size)");
}

image::~image()
{
    if(this->_stream != NULL)
        this->_stream->Release();

    if(this->_handle != NULL)
        ::GlobalFree(this->_handle);
}

//
// load
//  파일로부터 이미지를 로드한다.
//
// Parameters
//  filename        파일명
//
// Return
//  성공시 true, 실패시 false
//
bool image::load(const wchar_t* filename)
{
    this->_image                        = Image::FromFile(filename);
    if(this->_image == NULL)
        return false;

    return true;
}

//
// load
//  이미지 데이터로부터 이미지를 로드한다.
//
// Parameters
//  bytes       이미지 데이터
//  size        이미지 데이터 크기
//
// Return
//  성공시 true, 실패시 false
//
bool image::load(const void * bytes, int size)
{
    this->_handle                       = ::GlobalAlloc(GMEM_MOVEABLE, size);
    void*                   data        = ::GlobalLock(this->_handle);
    memcpy(data, bytes, size);
    ::GlobalUnlock(this->_handle);

    if(::CreateStreamOnHGlobal(this->_handle, true, &this->_stream) != S_OK)
        return false;

    if((this->_image = Image::FromStream(this->_stream)) == NULL)
        return false;

    return true;
}

void image::rotateVertical()
{
    this->_image->RotateFlip(Gdiplus::RotateFlipType::Rotate180FlipY);
}

void image::rotateHorizontal()
{
    this->_image->RotateFlip(Gdiplus::RotateFlipType::Rotate180FlipY);
}

void image::rotate(Gdiplus::RotateFlipType rotateType)
{
    this->_image->RotateFlip(rotateType);
}

unsigned int image::width() const
{
    return this->_image->GetWidth();
}

unsigned int image::height() const
{
    return this->_image->GetHeight();
}

image::Pivot image::pivot() const
{
    return this->_pivot;
}

image::operator Image*()
{
    return this->_image;
}

sprite::sprite(const wchar_t * filename)
{
    this->load(filename);
}

sprite::~sprite()
{
    for(auto i = this->_images.begin(); i != this->_images.end(); i++)
        delete i->second;
    this->_images.clear();
}

//
// load
//  파일로부터 스프라이트를 얻어온다.
//
// Parameters
//  filename        파일명
//
// Return
//  성공시 true, 실패시 false
//
bool sprite::load(const wchar_t * filename)
{
    try
    {
        std::ifstream           file(filename, std::ios::binary);
        if(file.is_open() == false)
            throw std::exception("Cannot find file");

        int                     count;
        file.read((char*)&count, sizeof(int));

        for(int i = 0; i < count; i++)
        {
            char                ksize   = 0;
            file.read(&ksize, sizeof(char));

            char*               key     = new char[ksize + 1];
            file.read(key, ksize);
            key[ksize]                  = 0;

            int                 pivot   = 0;
            file.read((char*)&pivot, sizeof(int));

            int                 bsize   = 0;
            file.read((char*)&bsize, sizeof(int));

            char*               bytes   = new char[bsize];
            file.read(bytes, bsize);

            this->_images.insert(std::make_pair(std::string(key), new image(bytes, bsize, (image::Pivot)pivot)));

            delete[] bytes;
            delete[] key;
        }

        file.close();
    }
    catch(std::exception&)
    {
        return false;
    }

    return true;
}

//
// get
//  스프라이트로부터 이미지를 얻어온다.
//
// Parameters
//  id      이미지 아이디
//
// Return
//  성공시 id에 대응되는 이미지, 실패시 NULL
// 
image * sprite::get(const std::string & id) const
{
    auto i = this->_images.find(id);
    if(i == this->_images.end())
        return NULL;

    return i->second;
}

image * sprite::operator[](const std::string & id)
{
    return this->get(id);
}