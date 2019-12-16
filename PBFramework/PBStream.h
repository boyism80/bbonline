#ifndef __FB_STREAM_H__
#define	__FB_STREAM_H__

#include <vector>
#include <algorithm>

namespace PB {

class stream : public std::vector<uint8_t>
{
public:
	enum endian { LITTLE = 0, BIG = 1};

protected:
	uint32_t				_position;
	uint32_t				_offset;

public:
	stream(uint32_t size = 1024);
	stream(const uint8_t* data, uint32_t size);
	virtual ~stream();

public:
	uint32_t				position() const;
};

class istream : public stream
{
public:
	istream(uint32_t size = 1024);
	istream(const uint8_t* data, uint32_t size);
	~istream();

public:
	int8_t					read_8();
	uint8_t					read_u8();
	int16_t					read_16(stream::endian endian = stream::endian::BIG);
	uint16_t				read_u16(stream::endian endian = stream::endian::BIG);
	int32_t					read_32(stream::endian endian = stream::endian::BIG);
	uint32_t				read_u32(stream::endian endian = stream::endian::BIG);
	void					read(void* stream, uint32_t size);
	uint32_t				readable_size() const;
	void					reset();
	void					shift(uint32_t size);
	void					flush();
};


class ostream : public stream
{
public:
	typedef std::vector<uint8_t>::iterator iterator;

public:
	ostream(uint32_t size = 1024);
	~ostream();

public:
	ostream&				write_8(int8_t value);
	ostream&				write_u8(uint8_t value);
	ostream&				write_16(int16_t value, stream::endian endian = stream::endian::BIG);
	ostream&				write_u16(uint16_t value, stream::endian endian = stream::endian::BIG);
	ostream&				write_32(int32_t value, stream::endian endian = stream::endian::BIG);
	ostream&				write_u32(uint32_t value, stream::endian endian = stream::endian::BIG);
	ostream&				write(const void* stream, uint32_t size);
	ostream&				write(const ostream& wb);
};

}

#endif // !__FB_STREAM_H__
