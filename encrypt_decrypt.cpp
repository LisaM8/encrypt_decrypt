#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to check if a file exists
bool fileExists(const string& filename) {
    ifstream file(filename);
    return file.good();
}

// Function to encrypt a given text using Caesar Cipher
string encryptText(const string& text, int shift) {
    string encryptedText = text;
    for (char& ch : encryptedText) {
        if (isalpha(ch)) {
            char base = isupper(ch) ? 'A' : 'a';
            ch = (ch - base + shift) % 26 + base;
        }
    }
    return encryptedText;
}

// Function to decrypt a given text using Caesar Cipher
string decryptText(const string& text, int shift) {
    return encryptText(text, 26 - shift);
}

// Function to read and process a file (encrypt or decrypt)
void processFile(const string& inputFile, const string& outputFile, int shift, bool encrypt) {
    if (!fileExists(inputFile)) {
        cout << "Error: File '" << inputFile << "' not found!\n";
        return;
    }

    ifstream inFile(inputFile);
    ofstream outFile(outputFile);

    if (!inFile || !outFile) {
        cout << "Error: Unable to open file.\n";
        return;
    }

    string line;
    cout << "\nProcessing...\n";
    while (getline(inFile, line)) {
        string processedText = encrypt ? encryptText(line, shift) : decryptText(line, shift);
        outFile << processedText << "\n";
    }

    inFile.close();
    outFile.close();
    cout << (encrypt ? "Encryption" : "Decryption") << " complete. File saved as: " << outputFile << endl;

    // Display the processed content
    cout << "\n===== Processed Content =====\n";
    ifstream resultFile(outputFile);
    while (getline(resultFile, line)) {
        cout << line << endl;
    }
    resultFile.close();
}

int main() {
    int choice, shift;
    string inputFile, outputFile;

    while (true) {
        cout << "\n===== FILE ENCRYPTION & DECRYPTION =====\n";
        cout << "1. Encrypt a File\n";
        cout << "2. Decrypt a File\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 3) {
            cout << "Exiting program. Goodbye!\n";
            break;
        }

        cout << "Enter input file name: ";
        cin >> inputFile;
        cout << "Enter output file name: ";
        cin >> outputFile;
        cout << "Enter shift key (1-25): ";
        cin >> shift;

        if (shift < 1 || shift > 25) {
            cout << "Invalid shift key! Must be between 1 and 25.\n";
            continue;
        }

        if (choice == 1)
            processFile(inputFile, outputFile, shift, true);
        else if (choice == 2)
            processFile(inputFile, outputFile, shift, false);
        else
            cout << "Invalid choice. Try again.\n";
    }

    return 0;
}
