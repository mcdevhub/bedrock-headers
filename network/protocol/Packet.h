#pragma once

#include "../NetworkIdentifier.h"
#include <string>

struct ReadOnlyBinaryStream {
	long long getVarInt64();
	int getSignedInt();
	float getFixedFloat(double);
	long long getSignedInt64();
	short getSignedShort();
	unsigned int getUnsignedInt();
	unsigned char getUnsignedChar();
	unsigned long long getUnsignedInt64();
	unsigned short getUnsignedShort();
	unsigned int getUnsignedVarInt();
	float getNormalizedFloat();
	unsigned long long getUnsignedVarInt64();
	int getSignedBigEndianInt();
	bool getBool();
	unsigned char getByte();
	float getFloat();
	double getDouble();
	std::string const& getString();
	int getVarInt();
};
struct BinaryStream : ReadOnlyBinaryStream {
	void writeFloat(float);
	void writeDouble(double);
	void writeStream(BinaryStream&);
	void writeString(std::string const&);
	void writeVarInt(int);
	void writeVarInt64(long long);
	void writeSignedInt(int);
	void writeFixedFloat(float, double);
	void writeSignedInt64(long long);
	void writeSignedShort(short);
	void writeUnsignedInt(unsigned int);
	void writeUnsignedChar(unsigned char);
	void writeUnsignedInt64(unsigned long long);
	void writeUnsignedShort(unsigned short);
	void writeUnsignedVarInt(unsigned int);
	void writeNormalizedFloat(float);
	void writeUnsignedVarInt64(unsigned long long);
	void writeSignedBigEndianInt(int);
	void write(void const*, unsigned int);
	void writeBool(bool);
	void writeByte(unsigned char);
};
struct NetEventCallback;

/*
 * Important: When creating a subclass include PacketTemplate.h inside the class
 */
struct Packet {
	int unk_4 = 2, unk_8 = 1;
	unsigned char playerSubIndex = 0;

	Packet() = default;

	Packet(unsigned char playerSubIndex) : playerSubIndex(playerSubIndex) {}

	Packet(Packet const &packet) : unk_4(packet.unk_4), unk_8(packet.unk_8) {}

	// Change these in PacketTemplate.h as well

	virtual ~Packet() = 0 ;

	virtual int getId() const = 0;

	virtual std::string getName() const = 0;

	virtual void write(BinaryStream &) const = 0;

	virtual void read(BinaryStream &) = 0;

	virtual void handle(NetworkIdentifier const &, NetEventCallback &) const = 0;

	virtual bool disallowBatching() const = 0;

	// The stuff above is 13 bytes
};