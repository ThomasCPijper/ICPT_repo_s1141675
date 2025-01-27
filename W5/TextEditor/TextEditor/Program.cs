public class TextEditor
{
    private static List<string> textLines = new List<string>();
    private static Stack<List<string>> undoStack = new Stack<List<string>>();
    private static Stack<List<string>> redoStack = new Stack<List<string>>();

    static void Main()
    {
        Console.WriteLine("Welcome to the Text Editor! Type lines or use commands.");
        Console.WriteLine("Commands: /EXIT, /UNDO, /REDO, /EDIT [Line Number], /ADD [Lines]");

        while (true)
        {
            Console.Write("> ");
            string input = Console.ReadLine();

            if (string.IsNullOrWhiteSpace(input))
                continue;

            if (input.StartsWith("/"))
            {
                if (input.Equals("/EXIT", StringComparison.OrdinalIgnoreCase))
                {
                    Console.WriteLine("Program exited.");
                    break;
                }
                else if (input.Equals("/UNDO", StringComparison.OrdinalIgnoreCase))
                {
                    Undo();
                }
                else if (input.Equals("/REDO", StringComparison.OrdinalIgnoreCase))
                {
                    Redo();
                }
                else if (input.StartsWith("/EDIT", StringComparison.OrdinalIgnoreCase))
                {
                    Edit(input);  // Pass-by-value
                }
                else if (input.StartsWith("/ADD", StringComparison.OrdinalIgnoreCase))
                {
                    AddLines(input);  // Params example
                }
                else
                {
                    Console.WriteLine("Unknown command.");
                }
            }
            else
            {
                AddLine(input);
            }
        }
    }

    // Pass-by-value
    private static void Edit(string command)
    {
        var parts = command.Split(' ');
        if (parts.Length != 2 || !int.TryParse(parts[1], out int lineNumber) || lineNumber < 1 || lineNumber > textLines.Count)
        {
            Console.WriteLine("Invalid command. Usage: /EDIT [Line Number]");
            return;
        }

        undoStack.Push(new List<string>(textLines));
        Console.WriteLine("Line to edit:");
        Console.WriteLine("-----------------------");
        Console.WriteLine(textLines[lineNumber - 1]);
        Console.WriteLine("-----------------------");
        Console.Write("New text: ");
        string newText = Console.ReadLine();

        textLines[lineNumber - 1] = newText;
        redoStack.Clear();
        PrintText();
    }

    // Pass-by-reference (Ref)
    private static void AddLine(ref string line)
    {
        undoStack.Push(new List<string>(textLines));
        textLines.Add(line);
        redoStack.Clear();
        PrintText();
    }

    private static void AddLine(string line)
    {
        undoStack.Push(new List<string>(textLines));
        textLines.Add(line);
        redoStack.Clear();
        PrintText();
    }

    // Pass-by-reference (Out)
    private static void TryGetLine(int lineNumber, out string line)
    {
        if (lineNumber >= 1 && lineNumber <= textLines.Count)
        {
            line = textLines[lineNumber - 1];
        }
        else
        {
            line = "Invalid line number.";
        }
    }

    // Params (Parameter Arrays)
    private static void AddLines(params string[] lines)
    {
        foreach (var line in lines)
        {
            textLines.Add(line);
        }
        PrintText();
    }
    
    private static Action<string> CreateEditAction(int lineNumber)
    {
        return (newText) =>
        {
            if (lineNumber >= 1 && lineNumber <= textLines.Count)
            {
                textLines[lineNumber - 1] = newText;  // Wijzig de regel
                PrintText();
            }
            else
            {
                Console.WriteLine("Invalid line number.");
            }
        };
    }

    private static void Undo()
    {
        if (undoStack.Count > 0)
        {
            redoStack.Push(new List<string>(textLines));
            textLines = undoStack.Pop();
            PrintText();
        }
        else
        {
            Console.WriteLine("Nothing to undo.");
        }
    }

    private static void Redo()
    {
        if (redoStack.Count > 0)
        {
            undoStack.Push(new List<string>(textLines));
            textLines = redoStack.Pop();
            PrintText();
        }
        else
        {
            Console.WriteLine("Nothing to redo.");
        }
    }

    private static void PrintText()
    {
        Console.WriteLine("--- Current Text ---");
        for (int i = 0; i < textLines.Count; i++)
        {
            Console.WriteLine($"{i + 1}: {textLines[i]}");
        }
        Console.WriteLine("-----------------------");
    }
}
