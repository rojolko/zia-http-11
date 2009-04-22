#include "FileReader.h"

FileReader::FileReader(const std::string &filePath)
{
	_fail = false;
	_file.open(filePath.c_str(), std::ifstream::binary);
	if (_file.fail())
		_fail = true;
	_file.seekg(0, std::ios::end);
	_fileSize = _file.tellg();
	_readRet = 0;
}

FileReader::~FileReader()
{

}

int		FileReader::getReadRet(void)
{
	return this->_readRet;
}

bool	FileReader::haveFail(void)
{
	return this->_fail;
}

int		FileReader::getFileSize(void)
{
	return this->_fileSize;
}

int		FileReader::getContentFile(char *buf, const int size)
{
	this->_file.seekg(0, std::ios::beg);
	this->_file.read(buf, size);
	this->_readRet = this->_file.gcount();
	return this->_readRet;
}