import { Disposable, window } from 'vscode';

import { KeywordHighlighter } from './keywordHighlighter';

class KeywordHighlighterController {
    private _keywordHighlighter: KeywordHighlighter;
    private _disposable: Disposable;

    constructor(highlighter: KeywordHighlighter) {
        this._keywordHighlighter = highlighter;

        // subscribe to selection change and editor activation events
        let subscriptions: Disposable[] = [];
        window.onDidChangeTextEditorSelection(this._onEvent, this, subscriptions);
        window.onDidChangeActiveTextEditor(this._onEvent, this, subscriptions);

        this._onEvent();

        // create a combined disposable from both event subscriptions
        this._disposable = Disposable.from(...subscriptions);
    }

    dispose() {
        this._disposable.dispose();
    }

    private _onEvent() {
        this._keywordHighlighter.updateHighlighting(window);
    }
}
