# pipex

pipex is a project that aims to replicate how two commands are piped together via '|' in the Shell.<br>
I've learned how pipes and child processes work in C while working on this project.<br>

## Usage

`make` to compile the program.<br>
`make bonus` to compile bonus.

`./pipex file1 "cmd1" "cmd2" file2` works like:<br>
`< file1 cmd1 | cmd2 > file2`

## Bonus
### Multiple pipes
`./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2` works like:<br>
`< file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2`<br><br>
### << and >> redirections
` ./pipex here_doc LIMITER cmd cmd1 file` works like:<br>
`cmd << LIMITER | cmd1 >> file`<br><br>
(you can use this bonus feature with multiple pipes as well.)<br><br>

### Notes

Keep in mind that this program only handles basic formats shown above and can't deal with special characters like $, ', *...<br><br>
It currently can't execute commands when given the path (/usr/bin/grep in place of grep etc.) but it should be easy enough to implement later on.<br><br>
The exit codes also aren't identical to the ones in bash.<br>
