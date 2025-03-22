
# AI-Powered Code Learning Platform

This project is an AI-powered code learning platform that combines interactive coding with AI-generated solutions, pseudocode, hints, and explanations. It allows users to write, run, and debug code while learning programming concepts interactively.

## Features

- **AI Code Generation**: Generate complete code, pseudocode, method signatures, and explanations for various programming topics.
- **Interactive Code Editor**: Write and run code directly in the browser.
- **Hints and Guidance**: Get specific hints to improve your code and learn better.
- **Multi-Language Support**: Supports C++, Python, Java, and JavaScript.
- **Modern UI**: A sleek, dark-themed interface with a 3D effect and animations.

---

## Installation

Follow these steps to set up the project on your local machine:

### Prerequisites

1. **Install C++ Compiler**:
   - For Linux: `sudo apt install g++`
   - For macOS: Install Xcode Command Line Tools: `xcode-select --install`
   - For Windows: Install MinGW or Visual Studio.

2. **Install Python**:
   - Download and install Python 3 from [python.org](https://www.python.org/).

3. **Install Node.js**:
   - Download and install Node.js from [nodejs.org](https://nodejs.org/).

4. **Install Java**:
   - Download and install the JDK from [oracle.com](https://www.oracle.com/java/technologies/javase-downloads.html).

5. **Install Dependencies**:
   - Install `cpp-httplib` and `nlohmann/json` libraries for C++.

6. **Install Bash**:
   - Ensure Bash is installed on your system (default on Linux/macOS, install Git Bash on Windows).

7. **Install Ollama LLM**:
   - Install the local LLM (e.g., `ollama`) and ensure it is configured properly.


### Steps to Run the Project

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-username/ai-code-learning-platform.git
   cd ai-code-learning-platform
   ```

2. **Set Up the Backend**:
   - Ensure the required C++ libraries (`cpp-httplib` and `nlohmann/json`) are available.
   - Compile and run the backend server:
     ```bash
     g++ -std=c++17 -o server main.cpp -lpthread
     ./server
     ```

3. **Set Up the Frontend**:
   - Open the `index.html` file in your browser:
     ```bash
     open index.html  # macOS
     xdg-open index.html  # Linux
     start index.html  # Windows
     ```

4. **Run the Application**:
   - Access the platform in your browser at `http://localhost:8080`.

---

## Usage

1. **Write Code**:
   - Use the left panel to write your code in the selected programming language.

2. **Generate AI Code**:
   - Enter a topic in the right panel and click "Generate Full Code" to get AI-generated solutions.

3. **Get Hints**:
   - Write your code and click "Get Hint" to receive specific guidance.

4. **Run Code**:
   - Click "Run Code" to execute your code and view the output.

5. **Explore Pseudocode**:
   - Click "Pseudocode" to view the algorithm's pseudocode.

---

## Project Structure

```
.
├── main.cpp          # Backend server code
├── index.html        # Frontend UI
├── README.md         # Project documentation
├── solution.txt      # Temporary file for AI responses
├── error_log.txt     # Temporary file for error logs
└── assets/           # (Optional) Additional assets like images or styles
```

---

## Screenshots

### Splash Screen
![Splash Screen](https://via.placeholder.com/800x400?text=Splash+Screen)

### Main Interface
![Main Interface](https://via.placeholder.com/800x400?text=Main+Interface)

---

## Technologies Used

- **Frontend**: HTML, CSS, JavaScript
- **Backend**: C++ (with `cpp-httplib` and `nlohmann/json`)
- **AI Integration**: Local LLM (e.g., `ollama`)
- **Languages Supported**: C++, Python, Java, JavaScript

---

## Contributors

- **Arjun Thilak** - [LinkedIn](https://www.linkedin.com/in/arjun-thilak-17248a247/)
- **Anish Sriram** - [LinkedIn](https://www.linkedin.com/in/anishsriram/)

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Future Enhancements

- Add support for more programming languages.
- Integrate a database to save user progress.
- Enhance AI prompts for better accuracy and formatting.
- Add real-time collaboration features.

---

## Contact

For any queries or feedback, please contact:
- **Arjun Thilak**: [arjun@example.com](mailto:arjun@example.com)
- **Anish Sriram**: [anish@example.com](mailto:anish@example.com)
```

Replace placeholder links and email addresses with actual ones before submission.

arjuniitm24: geive m ethe netore ocnnte in the reamd.md file 

GitHub Copilot: ### [README.md](file:///Users/mac/examap/README.md)

```markdown
# AI-Powered Code Learning Platform

This project is an AI-powered code learning platform that combines interactive coding with AI-generated solutions, pseudocode, hints, and explanations. It allows users to write, run, and debug code while learning programming concepts interactively.

---

## Features

- **AI Code Generation**: Generate complete code, pseudocode, method signatures, and explanations for various programming topics.
- **Interactive Code Editor**: Write and run code directly in the browser.
- **Hints and Guidance**: Get specific hints to improve your code and learn better.
- **Multi-Language Support**: Supports C++, Python, Java, and JavaScript.
- **Modern UI**: A sleek, dark-themed interface with a 3D effect and animations.

---

## Installation

### Prerequisites

1. **Install C++ Compiler**:
   - For Linux: `sudo apt install g++`
   - For macOS: Install Xcode Command Line Tools: `xcode-select --install`
   - For Windows: Install MinGW or Visual Studio.

2. **Install Python**:
   - Download and install Python 3 from [python.org](https://www.python.org/).

3. **Install Node.js**:
   - Download and install Node.js from [nodejs.org](https://nodejs.org/).

4. **Install Java**:
   - Download and install the JDK from [oracle.com](https://www.oracle.com/java/technologies/javase-downloads.html).

5. **Install Dependencies**:
   - Install `cpp-httplib` and `nlohmann/json` libraries for C++.

6. **Install Bash**:
   - Ensure Bash is installed on your system (default on Linux/macOS, install Git Bash on Windows).

7. **Install Ollama LLM**:
   - Install the local LLM (e.g., `ollama`) and ensure it is configured properly.

---

### Steps to Run the Project

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/your-username/ai-code-learning-platform.git
   cd ai-code-learning-platform
   ```

2. **Set Up the Backend**:
   - Ensure the required C++ libraries (`cpp-httplib` and `nlohmann/json`) are available.
   - Compile and run the backend server:
     ```bash
     g++ -std=c++17 -o server main.cpp -lpthread
     ./server
     ```

3. **Set Up the Frontend**:
   - Open the `index.html` file in your browser:
     ```bash
     open index.html  # macOS
     xdg-open index.html  # Linux
     start index.html  # Windows
     ```

4. **Run the Application**:
   - Access the platform in your browser at `http://localhost:8080`.

---

## Usage

1. **Write Code**:
   - Use the left panel to write your code in the selected programming language.

2. **Generate AI Code**:
   - Enter a topic in the right panel and click "Generate Full Code" to get AI-generated solutions.

3. **Get Hints**:
   - Write your code and click "Get Hint" to receive specific guidance.

4. **Run Code**:
   - Click "Run Code" to execute your code and view the output.

5. **Explore Pseudocode**:
   - Click "Pseudocode" to view the algorithm's pseudocode.

---

## Project Structure

```
.
├── main.cpp          # Backend server code
├── index.html        # Frontend UI
├── README.md         # Project documentation
├── solution.txt      # Temporary file for AI responses
├── error_log.txt     # Temporary file for error logs
└── assets/           # (Optional) Additional assets like images or styles
```

---

## Screenshots

### Splash Screen
![Splash Screen](https://via.placeholder.com/800x400?text=Splash+Screen)

### Main Interface
![Main Interface](https://via.placeholder.com/800x400?text=Main+Interface)

---

## Technologies Used

- **Frontend**: HTML, CSS, JavaScript
- **Backend**: C++ (with `cpp-httplib` and `nlohmann/json`)
- **AI Integration**: Local LLM (e.g., `ollama`)
- **Languages Supported**: C++, Python, Java, JavaScript

---

## Contributors

- **Arjun Thilak** - [LinkedIn](https://www.linkedin.com/in/arjun-thilak-17248a247/)
- **Anish Sriram** - [LinkedIn](https://www.linkedin.com/in/anishsriram/)

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

## Future Enhancements

- Add support for more programming languages.
- Integrate a database to save user progress.
- Enhance AI prompts for better accuracy and formatting.
- Add real-time collaboration features.

---

## Contact

For any queries or feedback, please contact:
- **Arjun Thilak**: [arjun@example.com](mailto:arjun@example.com)
- **Anish Sriram**: [anish@example.com](mailto:anish@example.com)
```

Replace placeholder links and email addresses with actual ones before submission.
