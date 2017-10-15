'use strict';
import { commands, Disposable, ExtensionContext, window } from 'vscode';


export function activate(context: ExtensionContext) {

    console.log('cog-lang extension activated!');

    let subscriptions: Disposable[] = [];

    // The command has been defined in the package.json file
    // Now provide the implementation of the command with  registerCommand
    // The commandId parameter must match the command field in package.json
    subscriptions.push(commands.registerCommand('extension.sayHello', () => {
        // The code you place here will be executed every time your command is executed

        // Display a message box to the user
        var editor = window.activeTextEditor;
        if (!editor) {
            return; // No open text editor
        }
        
        var selection = editor.selection;
        var text = editor.document.getText(selection);
        
        // Display a message box to the user
        window.showInformationMessage('Selected characters: ' + text.length);
    }));

    context.subscriptions.push(...subscriptions);
}

// this method is called when your extension is deactivated
export function deactivate() {
}
