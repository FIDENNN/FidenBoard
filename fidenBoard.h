#include <string>

namespace fidenBoard
{
    //Keyboard flags
    enum flags
    {
        flags_default = 0,
        flags_noNumbers = 1,
        flags_noCaps = 2,
    };



    class Size {
    public:
        int width = 800, height = 800;
    };

    Size size;
    

    class InputText {
    private:
        std::string text = "";
    public:
        std::string getText() { return this->text; }
        std::string* getAddress() { return &this->text; }
    };

    //KEYBOARD INPUT TEXT
    InputText inputText;
    //KEYBOARD INPUT TEXT

    class Properties {
    private: 
        flags flag = flags_default;

        void initSize(ImVec2 sizze) {
            size.width = (int)sizze.x;
            size.height = (int)sizze.y;
        }

    public:
        Properties(ImVec2 size, flags flag = flags_default) {
            setFlags(flag);
            initSize(size);
        }
        flags getFlags() { return this->flag; }
        void setFlags(flags flag) { this->flag = flag; }
    };



    class Lines {
        
    public:
        std::string lines[3] = {
            "qwertyuiop",
            "asdfghjkl",
            "zxcvbnm"
        };

        void toCaps(bool caps) {
            for (int i = 0; i < getSize(); i++) {
                std::string* str = &lines[i];
                for (int p = 0; p < lines[i].size(); p++) {
                    char* r = &lines[i][p];
                    if (caps) {
                        *r = toupper(*r);
                    }
                    else {
                        *r = tolower(*r);
                    }
                }
            }
        }

        int getSize() { return sizeof lines / sizeof lines[0]; }
    };


    Lines linez;



    namespace specialChars
    {
        class Canc {
        public:
            void add()
            {
                ImGui::SameLine();
                if (ImGui::Button("<-", { (float)size.width / 10.0f, (float)size.height / 10.0f })) {
                    std::string res;
                    if (inputText.getText().size() == 0) { return; }
                    for (int i = 0; i < (inputText.getText().size() - 1); i++) {
                        res += inputText.getText()[i];
                    }
                    *inputText.getAddress() = res;
                }
            }
        };


        bool isCaps = false;
        class Caps {
        private:
            
        public:
            void add()
            {
                ImGui::SameLine();
                if (ImGui::Button("Caps", { ImGui::GetWindowWidth() / 11, ImGui::GetWindowHeight() / 11 })) {
                    isCaps = !isCaps;
                    for (int i = 0; i < linez.getSize(); i++) {
                        std::string* str = &linez.lines[i];
                        for (int p = 0; p < linez.lines[i].size(); p++) {
                            char* r = &linez.lines[i][p];
                            if (isCaps) {
                                *r = toupper(*r);
                            }
                            else {
                                *r = tolower(*r);
                            }
                        }
                    }
                }
            }
        };

        class Space {
        public:
            void add() {
                if (ImGui::Button("----", { ImGui::GetWindowWidth(), (ImGui::GetWindowWidth() / 10) })) {
                    *inputText.getAddress() += ' ';
                }
            }
        };
    }





    class FidenBoard {
    private:
        Properties *properties;
        specialChars::Canc canc;
        specialChars::Space space;
        specialChars::Caps caps;

        void addKeyword(std::string carattere, float width) {
            if (ImGui::Button(carattere.c_str(), { (float)size.width / width, (float)size.height / width })) {
                *inputText.getAddress() += carattere;
            }
            ImGui::SameLine();
        }
        void addKeywordSameLine(std::string str, int width) {
            for (int i = 0; i < str.size(); i++) {
                std::string charTostring(1, str[i]);
                addKeyword(charTostring, width);
            }
            ImGui::Text("");
        }

    public:
        FidenBoard(ImVec2 size, flags flag = flags_default) {

            properties = new Properties(size, flag);

            switch (flag) {

            case flags_noNumbers:
            {
                addKeywordSameLine(linez.lines[0], 12);
                addKeywordSameLine(linez.lines[1], 12);
                caps.add();
                addKeywordSameLine(linez.lines[2], 9);
                canc.add();
                space.add();
            }break;

            case flags_noCaps:
            {
                addKeywordSameLine("123456789", 11);
                addKeywordSameLine(linez.lines[0], 12);
                addKeywordSameLine(linez.lines[1], 12);
                addKeywordSameLine(linez.lines[2], 9);
                canc.add();
                space.add();
            }break;

            default:
            {
                addKeywordSameLine("123456789", 11);
                addKeywordSameLine(linez.lines[0], 12);
                addKeywordSameLine(linez.lines[1], 12);
                caps.add();
                addKeywordSameLine(linez.lines[2], 9);
                canc.add();
                space.add();
            }break;
            }
           }
    };
}



