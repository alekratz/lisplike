#include "util.hpp"
#include "driver.hpp"
#include <iostream>

using namespace std;
namespace fs = boost::filesystem;

string pad_internal(const ll_children& terms, cstref inner)
{
    string result = "";
    for(auto it = terms.begin(); it != terms.end(); it++)
    {
        if(it + 1 == terms.end())
            result += (*it)->gencode();
        else
            result += (*it)->gencode() + inner;
    }
    return result;
}

bool create_directory_tree(const fs::path& outdir)
{
    for(auto outdir_part : outdir)
    {
        static fs::path outdir_full;
        outdir_full /= outdir_part;
        // ensure that the directory exists or can be created
        if(!exists(outdir_full))
        {
            VCERR << "creating directory " << outdir_full << endl;
            try
            {
                create_directory(outdir_full);
            }
            catch(fs::filesystem_error)
            {
                return false;
            }
        }
        else if(!is_directory(outdir_full))
        {
            cerr << outdir_full << " already exists as a non-directory file" << endl;
            return false;
        }
    }
    return true;
}