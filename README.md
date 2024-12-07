# Latex Generator

A C++ library designed to generate LaTeX documents programmatically. This library allows the user to create LaTeX documents with various sections, subsections, tables, and more. It also supports adding a table of contents, page breaks, and libraries.

## Features

- **Create Sections**: Add sections, subsections, and subsubsections to your LaTeX document.
- **Add Text**: Insert plain text into the document.
- **Add Table of Contents (TOC)**: Automatically generate a table of contents.
- **Insert Tables**: Add tables with customizable formatting and content.
- **Add Libraries**: Include additional LaTeX packages to your document.
- **Save the LaTeX file**: Save the generated LaTeX code into a `.tex` file.

## Requirements

- C++17 or higher.
- A LaTeX installation (e.g., TeX Live, MiKTeX) to compile the generated `.tex` files.

## Installation

1. Clone the repository or download the source code.
2. Compile the project using a C++11-compliant compiler. For example, if using `g++`:

    ```bash
    g++ -std=c++17 main.cpp -o latex_generator
    ```

3. Run the generated executable.

## Usage

### Command Line Arguments

- **path**: The path to the input file containing the document metadata and content.
- The input file should contain the document's title, author, and date on the first line, separated by semicolons (`;`).
- The content of the document follows, where:
  - Lines starting with `#`, `##`, or `###` are interpreted as section, subsection, and subsubsection headers respectively.
  - Lines starting with `@TOC` will generate a table of contents.
  - Any other lines are treated as plain text.

### Example Input File
```
My Document Title; Author Name; 2024-12-07

@TOC

# Section 1

Some text.

## Subsection 1.1

Things.

### Subsubsection 1.1.1

More things.

# Section 2

Another section.
```

The output will look like this:
```
\documentclass{article}

\title{My Document Title}
\author{Author Name}
\date{2024-12-07}

\begin{document}
\maketitle
\tableofcontents
\pagebreak

\section{Section 1}
Some text.

\subsection{Subsection 1.1}
Things.

\subsubsection{Subsubsection 1.1.1}
More things.

\section{Section 2}
Another section.
\end{document}
```

## TO-DO
* Add table from the file reader
* Modify the output file name from the command line
* Read .doc files
