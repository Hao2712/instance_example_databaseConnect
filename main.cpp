#include <iostream>
#include <mutex>
#include <string>

class DatabaseConnectionManager {
    private:
        static DatabaseConnectionManager* instance;
        static std::mutex mtx;
        bool isConnected;

        DatabaseConnectionManager() : isConnected(false) {
            std::cout << "Khoi tao quan ly ket noi co so du lieu" << std::endl;
        };

    public:
        static DatabaseConnectionManager* getInstance() {
            if(instance == nullptr) {
                std::lock_guard<std::mutex> lock(mtx);
                if(instance == nullptr) {
                    instance = new DatabaseConnectionManager();
                }
            }
            return instance; 
        }

        void connect() {
            if(!isConnected) {
                std::cout << "Dang ket noi den co so du lieu" << std::endl;
                isConnected = true;
            } else {
                std::cout << "Da ket noi den co so du lieu" << std::endl;
            }
        }

        void disConnect() {
            if(isConnected) {
                std::cout << "Dang ngat ket noi den co so du lieu" << std::endl;
                isConnected = false;
            } else {
                std::cout << "Da ngat ket noi den co so du lieu" << std::endl;
            }
        }

        void query(const std::string& sql) {
            if(isConnected) {
                std::cout << "Dang trich xuat query: " << sql << std::endl;
            } else {
                std::cout << "Khong co ket noi den co so du lieu" << std::endl;
            }
        }

        static void cleanup() {
            delete instance;
            instance = nullptr;
        }

};

DatabaseConnectionManager* DatabaseConnectionManager::instance = nullptr;
std::mutex DatabaseConnectionManager::mtx;

int main() {
    DatabaseConnectionManager* dbManager = DatabaseConnectionManager::getInstance();

    dbManager->connect();
    dbManager->query("Lua chon tu nguoi dung");
    dbManager->disConnect();
    dbManager->query("Lua chon tu nguoi dung");
    dbManager->disConnect();
}