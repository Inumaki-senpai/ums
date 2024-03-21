# Working with GitHub Remote Repositories Using Command Line

This guide will walk you through the process of working with GitHub remote repositories using the command line. We'll cover forking a branch, making changes in your local system, and raising a pull request to reflect changes in the original branch.

## Forking a Repository

1. Navigate to the repository you want to contribute to on GitHub.
2. Click on the **Fork** button in the top-right corner of the repository page.
3. This will create a copy of the repository in your GitHub account.

## Cloning the Forked Repository

1. Open your terminal.
2. Use the `git clone` command to clone your forked repository to your local system.

```bash
git clone <repository_url>
```

## Making Changes

1. Navigate to the cloned repository directory using the `cd` command.

```bash
cd <repository_name>
```

2. Create a new branch for your changes.

```bash
git checkout -b <branch_name>
```

3. Make your desired changes to the files in the repository using your preferred text editor.
4. Stage your changes for commit.

```bash
git add .
```

5. Commit your changes with a descriptive commit message.

```bash
git commit -m "Your commit message here"
```


## Pushing Changes to GitHub

1. Push your changes to your forked repository on GitHub.

```bash
git push origin <branch_name>
```


## Creating a Pull Request

1. Navigate to your forked repository on GitHub.
2. Click on the **New pull request** button next to your branch name.
3. Review your changes and ensure everything looks correct.
4. Click on the **Create pull request** button.
5. Add a title and description for your pull request explaining the changes.
6. Click on the **Create pull request** button to submit it.

Congratulations! You have successfully forked a repository, made changes, and raised a pull request to reflect those changes in the original branch.


