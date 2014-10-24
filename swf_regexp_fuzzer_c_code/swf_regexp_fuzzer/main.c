#include "src/regfuzz.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <time.h>


std::string re_prev_template("var a:RegExp = new RegExp(\"");
std::string re_post_template("\");");
std::string template_file_content;

std::string PrevProcessTheRe(char* new_content) {
    std::string processed_re;
    for (int i = 0; new_content[i] != 0; ++i) {
        if (new_content[i] == '\\') {
            processed_re.push_back(new_content[i]);
        }
        processed_re.push_back(new_content[i]);
    }
    return processed_re;
}

std::string ProcessTemplateFileContent (const std::string& template_file_content, 
                                        char* new_content, std::string file_name) {
    std::string new_re_content = PrevProcessTheRe(new_content);

    std::string file_content = "package\n{\n\timport\tflash.display.Sprite;\n\n\tpublic\tclass\t";
    file_content += file_name;
    file_content += "\textends\tSprite\n\t{\n\t\tpublic\tfunction\t";
    file_content += file_name;
    file_content += "()\n\t\t{\n\t\t\t";
    file_content += re_prev_template;
    file_content += new_re_content;
    file_content += re_post_template;
    file_content += "\n\t\t}\n\t}\n}";

    return file_content;
}

void WriteNewAs3ContentToFile(const std::string& new_as3_content, std::string file_name) {
    std::string file_path("as3_files_output\\");
    file_name += ".as";
    file_path += file_name;
    std::ofstream new_as3_file(file_path);
    if (!new_as3_file.is_open()) {
        printf("out put as file is not opened!\n");
        return;
    }
    new_as3_file << new_as3_content;
}

std::string GenerateFileName() {
    static unsigned int count = 0;
    std::string file_name("swf_re_fuzz_sample_");
    char buf[100] = {0};
    ++count;
    itoa(count, buf, 10);
    file_name += buf;
    //file_name += ".as";
    return file_name;
}


void Generate_As3File_UseTemplate(std::string& template_file_name, char* new_content) {
    std::string file_name = GenerateFileName();
    std::string new_file_content = ProcessTemplateFileContent(template_file_content, new_content, file_name);
    WriteNewAs3ContentToFile(new_file_content, file_name);

    /*std::ifstream template_file;
    template_file.open(template_file_name);
    if (template_file.is_open()) {
        std::string as3_content;
        std::string tmp;
        while(getline(template_file, tmp)){
            as3_content += tmp;
            as3_content += "\n";
        }
        ProcessTemplateFileContent(as3_content, new_content, file_name);
        WriteNewAs3ContentToFile(as3_content, file_name);

    } else {
        printf("can not open template file!\n");
        return;
    }*/
}

unsigned int g_num_of_samples_to_generate = 1;

int main(int argc, char **argv)
{
    char* re = NULL;
    if (argc < 4) {
        fprintf(stderr, "usage: %s [lenbias] [template_file_name] [num_of_samples]\n", *argv);
        return 1;
    }

    _set_seed(time(NULL));
    unsigned lenbias = atol(argv[1]);
    std::string template_file_name(argv[2]);
    g_num_of_samples_to_generate = atol(argv[3]);

    for (int i = 0; i < g_num_of_samples_to_generate; ++i) {
        re = _getregex(lenbias, 0);
        //fprintf(stdout, "%s", re);
        Generate_As3File_UseTemplate(template_file_name, re);
    }
    
    return 0;
}