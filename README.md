# 🐚 Minishell - 42 Porto

A custom UNIX command-line interpreter written in C, replicating core Bash functionalities.

## 🚀 Features
### Core Functionality
- **Command execution** with absolute/relative paths (`/bin/ls` or `./program`)
- **Environment variables** (`$PATH` expansion)
- **Redirections**: `<` (input), `>` (output), `>>` (append), `<<` (heredoc)
- **Pipes** (`|`) with multi-pipe support (`cmd1 | cmd2 | cmd3`)
- **Signal handling** for `Ctrl-C` (interrupt), `Ctrl-\` (quit), `Ctrl-D` (EOF)

### My Key Contributions
✔ **Lexer/Parser System**  
- Implemented tokenization with state machine for quotes (`'`, `"`) and special chars (`|`, `>`)  

✔ **Environment Variables & Expansion**  
- Designed `$VAR` expansion with proper scoping rules  
- Implemented special variables (`$?`, `$$`)  
- Handled edge cases: `echo "$USER"` vs `echo '$USER'`  

✔ **Heredoc Implementation**  
- Created delimiter-based input system (`<< EOF`)  
- Supported variable expansion in heredoc blocks  
- Prevented SIGINT interruption during heredoc input  

✔ **Memory Management**  
- Zero-leak guarantee via rigorous allocation tracking  
- Safe garbage collection system for orphaned processes  

✔ **Builtins**  
- `cd` with relative/absolute path  
- `export`/`unset` with syntax validation  

## 🛠️ Installation
```bash
git clone https://github.com/mfortuna23/minishell
cd minishell && make
./minishell
```

<img width="879" height="530" alt="image" src="https://github.com/user-attachments/assets/dfc61224-10cd-4a91-aece-627eb2c6c970" />

 
 Sources :
 https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
 devdocs.io
 https://www.linux.org/threads/bash-03-%E2%80%93-command-line-processing.38676/
 https://www.youtube.com/watch?v=NkfIUo_Qq4c
