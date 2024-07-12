import Foundation

func runShellCommand(_ command: String) {
    let task = Process()
    task.launchPath = "/bin/bash"
    task.arguments = ["-c", command]
    task.launch()
    task.waitUntilExit()
}

func main() {
    // Source files
    let sources = [
        "src/main.c++",
        "src/errors.c++",
        "src/parser/boolean.c++",
        "src/parser/string.c++",
        "src/token.c++",
        "src/parser.c++",
    ]

    // Compile each source file
    for source in sources {
        let objectFile = "\(source).o"
        let compilerFlags = "-std=c++17 -Wall" // Adjust flags as needed
        let includeDirs = ["./src"]
        let includeFlags = includeDirs.map { "-I\($0)" }.joined(separator: " ")
        runShellCommand("g++ \(compilerFlags) \(includeFlags) -c \(source) -o \(objectFile)")
    }

    // Link object files into executable
    let objectFiles = sources.map { "\($0).o" }
    let executableName = "YourExecutable"
    runShellCommand("g++ \(objectFiles.joined(separator: " ")) -o \(executableName)")
}

main()
