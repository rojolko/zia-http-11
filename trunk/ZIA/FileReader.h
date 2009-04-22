#ifndef _FILEREADER_H_
#define _FILEREADER_H_

#include <iostream>
#include <fstream>
#include <string>

class						FileReader
{
private:
	int						_fileSize;
	int						_readRet;
	bool					_fail;
	std::ifstream	_file;
public:
	FileReader(const std::string &filePath);
	~FileReader();

	int		getFileSize(void);
	int		getReadRet(void);
	bool	haveFail(void);

	int		getContentFile(char *buf, const int size);

};

#endif