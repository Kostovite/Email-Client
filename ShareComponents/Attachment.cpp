#include "Attachment.h"

#include <iostream>

using std::cout, std::endl;

Attachment::Attachment()
{
	_fileName = "";
	_filePath = "";
}

Attachment::Attachment(string fileName, string filePath)
{
	_fileName = fileName;
	_filePath = filePath;
}

Attachment::~Attachment()
{
}

string Attachment::getFileName()
{
	return _fileName;
}

string Attachment::getFilePath()
{
	return _filePath;
}

string Attachment::getFileType()
{
	string fileType = "";
	size_t i = _fileName.length() - 1;
	while (_fileName[i] != '.') {
		fileType = _fileName[i] + fileType;
		i--;
	}
	return fileType;
}

void Attachment::setFileName(string fileName)
{
	_fileName = fileName;
}

void Attachment::setFilePath(string filePath)
{
	_filePath = filePath;
}

void Attachment::printAttachmentDetails()
{
	cout << "File name: " << _fileName << endl;
	cout << "File path: " << _filePath << endl;
	cout << "File type: " << getFileType() << endl;
}
