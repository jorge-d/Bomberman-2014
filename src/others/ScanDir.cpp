#include "ScanDir.hh"

ScanDir::ScanDir(const char *path) :
  fail_(false), path_(path), dp_(opendir(path))
{
  if (this->dp_ == NULL)
    {
      this->fail_ = true;
      std::cerr << "Couldn't open directory '" << path << "'" << std::endl;
    }
}

ScanDir::~ScanDir(void)
{
  if (this->fail_ == false)
    (void) closedir(this->dp_);
}

bool ScanDir::getFilesFromExtension(std::vector<std::string> &res, const std::string& ext) const
{
  struct dirent *e;

  while ((e = readdir(this->dp_)))
    {
      std::string filename = e->d_name;

      if (filename.length() > 4 &&
	  filename.substr(filename.length() - 4, 4) == "."+ext)
	res.push_back(this->path_ + filename);
    }
  return (res.size() ? true : false);
}

bool ScanDir::operator!(void) const
{
  return !this->isOk();
}

bool ScanDir::isOk(void) const
{
  return !this->fail_;
}
