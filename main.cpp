#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <map>
#include <unordered_map>
#include "cpp-httplib/httplib.h"
#include "json/single_include/nlohmann/json.hpp"

using json = nlohmann::json;
using namespace httplib;

// Structure to store comprehensive learning material
struct LearningMaterial {
    std::string code;                // Complete solution code
    std::string language;            // Programming language
    std::string topic;               // Topic/algorithm name
    std::string pseudocode;          // Algorithm pseudocode
    std::string methodSignatures;    // Method signatures/structure
    std::string explanation;         // Detailed explanation
    std::string prompt;              // Original prompt used to generate
};

// Global storage for generated solutions and learning materials
std::unordered_map<std::string, LearningMaterial> learningMaterialStorage;

// Function to escape special characters for system commands
std::string escapeString(const std::string& input) {
    std::string output = input;
    size_t pos = 0;
    while ((pos = output.find("\"", pos)) != std::string::npos) {
        output.replace(pos, 1, "\\\"");
        pos += 2;
    }
    return output;
}

// Function to get AI completion from Ollama
std::string getAICompletion(const std::string& prompt, const std::string& language, const std::string& type = "code") {
    // Modify prompt based on what we want to generate
    std::string fullPrompt;
    
    if (type == "code") {
        fullPrompt = "Write a complete " + language + " program for: " + prompt;
    } else if (type == "pseudocode") {
        fullPrompt = "Write detailed pseudocode for solving: " + prompt;
    } else if (type == "method_signatures") {
        fullPrompt = "Write only the method signatures and data structures needed for a " + language + " program that: " + prompt;
    } else if (type == "explanation") {
        fullPrompt = "Explain in detail the algorithm and approach for: " + prompt;
    } else if (type == "hint") {
        fullPrompt = prompt; // For hints, we'll pass the complete customized prompt
    }
    
    std::string escapedPrompt = escapeString(fullPrompt);
    std::string command = "/bin/bash -c 'ollama run qwen2.5-coder:0.5b \"" + escapedPrompt + "\" > solution.txt 2> error_log.txt'";
    system(command.c_str());
    
    std::ifstream file("solution.txt");
    std::string response, line;
    while (getline(file, line)) {
        response += line + "\n";
    }
    file.close();
    
    return response;
}

// Function to generate hints based on user code
std::string generateHint(const std::string& userCode, const std::string& topic, const std::string& language) {
    // First, check if we have the solution for this topic
    std::string solutionKey = topic + "_" + language;
    
    if (learningMaterialStorage.find(solutionKey) == learningMaterialStorage.end()) {
        // Generate a basic solution first if we don't have one
        std::string code = getAICompletion(topic, language, "code");
        
        LearningMaterial newMaterial;
        newMaterial.code = code;
        newMaterial.language = language;
        newMaterial.topic = topic;
        learningMaterialStorage[solutionKey] = newMaterial;
    }
    
    // Get the reference solution
    std::string referenceSolution = learningMaterialStorage[solutionKey].code;
    
    // Create a prompt that asks for hints by comparing the user's code with the reference
    std::string hintPrompt = "DOnt give me entire code this prompt is only for getting hints from you , I'm working on a " + language + " program for: " + topic + "\n\n";
    hintPrompt += "Here's my current code:\n\n```" + language + "\n" + userCode + "\n```\n\n";
    hintPrompt += "I'm stuck here and need a hint to proceed with this " + topic + " algorithm. ";
    hintPrompt += "Provide 3 specific, helpful hints that will guide me toward completion without directly giving away the complete solution. ";
    hintPrompt += "Focus on any logical errors, missing steps, or improvements, and explain why these changes would be beneficial. ";
    hintPrompt += "If my solution appears to be on the right track but incomplete, suggest what I should focus on next.";
    
    return getAICompletion(hintPrompt, language, "hint");
}

// Function to read HTML file
std::string readHtmlFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return "File not found: " + filename;
    }
    
    std::string content, line;
    while (getline(file, line)) {
        content += line + "\n";
    }
    file.close();
    
    return content;
}

// Function to run code in different languages
std::string runCode(const std::string& code, const std::string& language) {
    std::string output;
    
    // Create temporary files
    std::string fileExtension;
    std::string compileCommand;
    std::string runCommand;
    
    if (language == "cpp") {
        fileExtension = ".cpp";
        compileCommand = "g++ temp_code.cpp -o temp_program 2> compile_error.txt";
        runCommand = "./temp_program > output.txt 2>> compile_error.txt";
    } 
    else if (language == "python") {
        fileExtension = ".py";
        compileCommand = ""; // No compilation needed
        runCommand = "python3 temp_code.py > output.txt 2> compile_error.txt";
    }
    else if (language == "java") {
        fileExtension = ".java";
        // Assuming the code has a Main class
        compileCommand = "javac temp_code.java 2> compile_error.txt";
        runCommand = "java Main > output.txt 2>> compile_error.txt";
    }
    else if (language == "javascript") {
        fileExtension = ".js";
        compileCommand = ""; // No compilation needed
        runCommand = "node temp_code.js > output.txt 2> compile_error.txt";
    }
    else {
        return "Unsupported language: " + language;
    }
    
    // Write code to temporary file
    std::ofstream codeFile("temp_code" + fileExtension);
    codeFile << code;
    codeFile.close();
    
    // Compile if needed
    if (!compileCommand.empty()) {
        int compileResult = system(compileCommand.c_str());
        if (compileResult != 0) {
            std::ifstream errorFile("compile_error.txt");
            std::string errorLine;
            std::string errorOutput;
            while (getline(errorFile, errorLine)) {
                errorOutput += errorLine + "\n";
            }
            errorFile.close();
            return "Compilation Error: " + errorOutput;
        }
    }
    
    // Run the code
    int runResult = system(runCommand.c_str());
    
    // Read output
    std::ifstream outputFile("output.txt");
    std::string outputLine;
    while (getline(outputFile, outputLine)) {
        output += outputLine + "\n";
    }
    outputFile.close();
    
    // Check for runtime errors
    if (runResult != 0) {
        std::ifstream errorFile("compile_error.txt");
        std::string errorLine;
        std::string errorOutput;
        while (getline(errorFile, errorLine)) {
            errorOutput += errorLine + "\n";
        }
        errorFile.close();
        
        if (errorOutput.empty()) {
            return "Runtime Error (no details available)";
        } else {
            return "Runtime Error: " + errorOutput;
        }
    }
    
    // Clean up temporary files (optional in production)
    system("rm -f temp_code* temp_program output.txt compile_error.txt");
    
    return output;
}

int main() {
    // Create a server
    Server svr;
    
    // Serve the HTML page from a file
    svr.Get("/", [](const Request& req, Response& res) {
        std::string html = readHtmlFile("index.html");
        res.set_content(html, "text/html");
    });
    
    // API endpoint to generate code and learning materials
    svr.Post("/generate", [](const Request& req, Response& res) {
        json data = json::parse(req.body);
        std::string topic = data["topic"];
        std::string language = data.contains("language") ? data["language"] : "cpp";
        std::string type = data.contains("type") ? data["type"] : "full_code";
        
        if (topic.empty()) {
            json error_response;
            error_response["error"] = "No topic provided";
            res.set_content(error_response.dump(), "application/json");
            return;
        }
        
        // Generate a unique key for the solution
        std::string materialKey = topic + "_" + language;
        
        // Create response object
        json response;
        
        // Set fromCache flag to indicate if content is from cache
        bool fromCache = false;
        
        // For full code, check if we already have the solution
        if (type == "full_code" || type == "code") {
            if (learningMaterialStorage.find(materialKey) != learningMaterialStorage.end()) {
                // Return code from cache
                response["code"] = learningMaterialStorage[materialKey].code;
                response["fromCache"] = true;
                
                // Return other available materials if we have them
                if (!learningMaterialStorage[materialKey].pseudocode.empty())
                    response["pseudocode"] = learningMaterialStorage[materialKey].pseudocode;
                
                if (!learningMaterialStorage[materialKey].methodSignatures.empty())
                    response["methodSignatures"] = learningMaterialStorage[materialKey].methodSignatures;
                
                if (!learningMaterialStorage[materialKey].explanation.empty())
                    response["explanation"] = learningMaterialStorage[materialKey].explanation;
                
                res.set_content(response.dump(), "application/json");
                return;
            }
            
            // Generate new solution
            std::string code = getAICompletion(topic, language, "code");
            
            // Store the solution if not already in storage
            if (learningMaterialStorage.find(materialKey) == learningMaterialStorage.end()) {
                LearningMaterial newMaterial;
                newMaterial.code = code;
                newMaterial.language = language;
                newMaterial.topic = topic;
                learningMaterialStorage[materialKey] = newMaterial;
            } else {
                learningMaterialStorage[materialKey].code = code;
            }
            
            // Return the solution
            response["code"] = code;
            response["fromCache"] = false;
        }
        else if (type == "pseudocode") {
            // Check if pseudocode already exists in storage
            if (learningMaterialStorage.find(materialKey) != learningMaterialStorage.end() &&
                !learningMaterialStorage[materialKey].pseudocode.empty()) {
                response["pseudocode"] = learningMaterialStorage[materialKey].pseudocode;
                response["fromCache"] = true;
            } else {
                // Generate pseudocode
                std::string pseudocode = getAICompletion(topic, language, "pseudocode");
                
                // Store it
                if (learningMaterialStorage.find(materialKey) == learningMaterialStorage.end()) {
                    LearningMaterial newMaterial;
                    newMaterial.language = language;
                    newMaterial.topic = topic;
                    newMaterial.pseudocode = pseudocode;
                    learningMaterialStorage[materialKey] = newMaterial;
                } else {
                    learningMaterialStorage[materialKey].pseudocode = pseudocode;
                }
                
                response["pseudocode"] = pseudocode;
                response["fromCache"] = false;
            }
        }
        else if (type == "method_signatures") {
            // Check if method signatures already exist in storage
            if (learningMaterialStorage.find(materialKey) != learningMaterialStorage.end() &&
                !learningMaterialStorage[materialKey].methodSignatures.empty()) {
                response["methodSignatures"] = learningMaterialStorage[materialKey].methodSignatures;
                response["fromCache"] = true;
            } else {
                // Generate method signatures
                std::string methodSigs = getAICompletion(topic, language, "method_signatures");
                
                // Store it
                if (learningMaterialStorage.find(materialKey) == learningMaterialStorage.end()) {
                    LearningMaterial newMaterial;
                    newMaterial.language = language;
                    newMaterial.topic = topic;
                    newMaterial.methodSignatures = methodSigs;
                    learningMaterialStorage[materialKey] = newMaterial;
                } else {
                    learningMaterialStorage[materialKey].methodSignatures = methodSigs;
                }
                
                response["methodSignatures"] = methodSigs;
                response["fromCache"] = false;
            }
        }
        else if (type == "explanation") {
            // Check if explanation already exists in storage
            if (learningMaterialStorage.find(materialKey) != learningMaterialStorage.end() &&
                !learningMaterialStorage[materialKey].explanation.empty()) {
                response["explanation"] = learningMaterialStorage[materialKey].explanation;
                response["fromCache"] = true;
            } else {
                // Generate explanation
                std::string explanation = getAICompletion(topic, language, "explanation");
                
                // Store it
                if (learningMaterialStorage.find(materialKey) == learningMaterialStorage.end()) {
                    LearningMaterial newMaterial;
                    newMaterial.language = language;
                    newMaterial.topic = topic;
                    newMaterial.explanation = explanation;
                    learningMaterialStorage[materialKey] = newMaterial;
                } else {
                    learningMaterialStorage[materialKey].explanation = explanation;
                }
                
                response["explanation"] = explanation;
                response["fromCache"] = false;
            }
        }
        
        res.set_content(response.dump(), "application/json");
    });
    
    // API endpoint for generating hints
    svr.Post("/get-hint", [](const Request& req, Response& res) {
        json data = json::parse(req.body);
        std::string code = data["code"];
        std::string topic = data["topic"];
        std::string language = data.contains("language") ? data["language"] : "cpp";
        
        if (code.empty()) {
            json error_response;
            error_response["error"] = "No code provided";
            res.set_content(error_response.dump(), "application/json");
            return;
        }
        
        if (topic.empty()) {
            json error_response;
            error_response["error"] = "No topic provided";
            res.set_content(error_response.dump(), "application/json");
            return;
        }
        
        // Generate hint with updated prompt that indicates the user is stuck
        std::string hint = generateHint(code, topic, language);
        
        // Generate explanation if we don't have it yet
        std::string materialKey = topic + "_" + language;
        if (learningMaterialStorage.find(materialKey) != learningMaterialStorage.end() && 
            learningMaterialStorage[materialKey].explanation.empty()) {
            std::string explanation = getAICompletion(topic, language, "explanation");
            learningMaterialStorage[materialKey].explanation = explanation;
        }
        
        json response;
        response["hint"] = hint;
        
        // Include explanation if available
        if (learningMaterialStorage.find(materialKey) != learningMaterialStorage.end() && 
            !learningMaterialStorage[materialKey].explanation.empty()) {
            response["explanation"] = learningMaterialStorage[materialKey].explanation;
        }
        
        res.set_content(response.dump(), "application/json");
    });
    svr.Post("/generate-custom", [](const Request& req, Response& res) {
    json data = json::parse(req.body);
    std::string customPrompt = data["prompt"];
    std::string language = data.contains("language") ? data["language"] : "cpp";
    
    if (customPrompt.empty()) {
        json error_response;
        error_response["error"] = "No prompt provided";
        res.set_content(error_response.dump(), "application/json");
        return;
    }
    
    // Generate custom code based on user's prompt
    std::string customCode = getAICompletion(customPrompt, language, "code");
    
    json response;
    response["code"] = customCode;
    
    res.set_content(response.dump(), "application/json");
});
    // API endpoint to run code
    svr.Post("/run", [](const Request& req, Response& res) {
        json data = json::parse(req.body);
        std::string code = data["code"];
        std::string language = data["language"];
        
        if (code.empty()) {
            json error_response;
            error_response["error"] = "No code provided";
            res.set_content(error_response.dump(), "application/json");
            return;
        }
        
        std::string output = runCode(code, language);
        
        json response;
        // Check if the output starts with "Compilation Error" or "Runtime Error"
        if (output.find("Compilation Error") == 0 || output.find("Runtime Error") == 0) {
            response["error"] = output;
        } else {
            response["output"] = output;
        }
        
        res.set_content(response.dump(), "application/json");
    });
    
    // API endpoint to get saved user code (optional)
    svr.Post("/get-saved-code", [](const Request& req, Response& res) {
        json data = json::parse(req.body);
        std::string topic = data["topic"];
        std::string language = data["language"];
        
        // In a real app, this would fetch from a database
        // For now, we'll return an empty response as this is handled client-side
        json response;
        response["code"] = "";
        res.set_content(response.dump(), "application/json");
    });
    
    // API endpoint to get all stored learning materials (for admin/debugging)
    svr.Get("/learning-materials", [](const Request& req, Response& res) {
        json response = json::array();
        
        for (const auto& item : learningMaterialStorage) {
            json material;
            material["key"] = item.first;
            material["topic"] = item.second.topic;
            material["language"] = item.second.language;
            material["hasCode"] = !item.second.code.empty();
            material["hasPseudocode"] = !item.second.pseudocode.empty();
            material["hasMethodSignatures"] = !item.second.methodSignatures.empty();
            material["hasExplanation"] = !item.second.explanation.empty();
            response.push_back(material);
        }
        
        res.set_content(response.dump(), "application/json");
    });
    
    // Start the server
    std::cout << "Learning Platform Server running on http://localhost:8080\n";
    std::cout << "Open your web browser and navigate to http://localhost:8080\n";
    svr.listen("0.0.0.0", 8080);
    
    return 0;
}