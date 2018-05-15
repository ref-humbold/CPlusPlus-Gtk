/// <reference path="jquery.d.ts"/>

//#region

let board: Board = null;

abstract class Board {
    private static readonly LEFT_MOUSE: number = 1;
    private static readonly MIDDLE_MOUSE: number = 2;
    flagsLeft: number;
    clicks: number;
    shots: number;
    isReady: boolean;
    protected lastClickPos: number;

    constructor() {
        this.restart();
    }

    abstract restart(): void;

    showBombs(): void {
        this.getFieldsWithBombs()
            .css({
                "background-image": "url(\"images/bomba.jpg\")",
                "background-size": "100% 100%",
                "border-style": "solid"
            });
    }

    mouseClicked(event: JQuery.Event<Element>) {
        if (event.which == Board.LEFT_MOUSE)
            this.leftClick(event.target);
        else if (event.which == Board.MIDDLE_MOUSE)
            this.middleClick(event.target);
    }

    leftClick(element: Element): void {
        this.lastClickPos = parseInt(element.id, 10);
    }

    middleClick(element: Element): void {
        this.lastClickPos = parseInt(element.id, 10);
    }

    endGame(isWinner: boolean) {
        $("div.field").off("mousedown");
        $("div.field").on("mousedown", this.clickNothing);

        if (isWinner)
            $("div.face").css({ "background-image": "url(\"images/winface.jpg\")" });
        else
            $("div.face").css({ "background-image": "url(\"images/sadface.jpg\")" });
    }

    protected abstract getFieldsWithBombs(): JQuery<HTMLElement>;

    private clickNothing(event: JQuery.Event<Element>): void {
    }
}

class NormalBoard extends Board {
    private fields: Array<number>;
    private visible: Array<number>;

    constructor() {
        super();
    }

    restart() {
        this.fields = [];
        this.visible = [];
        this.flagsLeft = 40;
        this.clicks = 0;
        this.shots = 0;
        this.isReady = false;

        for (let i = 0; i < 256; ++i) {
            this.fields.push(0);
            this.visible.push(0);
        }
    }

    getFieldsWithBombs(): JQuery<HTMLElement> {
        return $("div.field")
            .filter((index: number, elem: Element) =>
                this.isBomb(parseInt(elem.id, 10))
            );
    }

    leftClick(element: Element): void {
        throw new Error("Method not implemented.");
    }

    middleClick(element: Element): void {
        throw new Error("Method not implemented.");
    }

    private isBomb(pos: number) {
        return this.fields[pos] == -1;
    }

    private isEmpty(pos: number) {
        return this.fields[pos] == 0;
    }

    private isNotVisible(pos: number) {
        return this.visible[pos] == 0;
    }
}

class TrollBoard extends Board {
    constructor() {
        super();
    }

    restart(): void {
        throw new Error("Method not implemented.");
    }

    getFieldsWithBombs(): JQuery<HTMLElement> {
        let randPos: number = 0;
        let bombs: Array<number> = [this.lastClickPos];

        for (let i = 0; i < 39; ++i) {
            do
                randPos = Math.floor(Math.random() * 255);
            while (bombs.indexOf(randPos) >= 0);

            bombs.push(randPos);
        }

        return $("div.field")
            .filter((index: number, elem: Element) =>
                bombs.indexOf(parseInt(elem.id, 10)) >= 0
            );
    }

    leftClick(element: Element): void {
        throw new Error("Method not implemented.");
    }

    middleClick(element: Element): void {
        throw new Error("Method not implemented.");
    }
}

//#endregion

let normal: NormalGame = null;
let troll: TrollGame = null;

class NormalGame {
    flagsLeft: number;
    clicks: number;
    shots: number;
    isReady: boolean;
    private fields: Array<number>;
    private visible: Array<number>;

    constructor() {
        this.restart();
    }

    restart() {
        this.fields = [];
        this.visible = [];
        this.flagsLeft = 40;
        this.clicks = 0;
        this.shots = 0;
        this.isReady = false;

        for (let i = 0; i < 256; ++i) {
            this.fields.push(0);
            this.visible.push(0);
        }
    }

    prepare(pos: number) {
        let bombs = this.randBombs(pos);
        this.isReady = true;

        for (let i = 0; i < bombs.length; ++i) {
            let row: number = Math.floor(bombs[i] / 16);
            let column: number = bombs[i] % 16;

            this.fields[bombs[i]] = -1;

            if (row > 0 && column > 0 && this.fields[bombs[i] - 16 - 1] >= 0)
                ++this.fields[bombs[i] - 16 - 1];

            if (row > 0 && this.fields[bombs[i] - 16] >= 0)
                ++this.fields[bombs[i] - 16];

            if (row > 0 && column < 15 && this.fields[bombs[i] - 16 + 1] >= 0)
                ++this.fields[bombs[i] - 16 + 1];

            if (column > 0 && this.fields[bombs[i] - 1] >= 0)
                ++this.fields[bombs[i] - 1];

            if (column < 15 && this.fields[bombs[i] + 1] >= 0)
                ++this.fields[bombs[i] + 1];

            if (row < 15 && column > 0 && this.fields[bombs[i] + 16 - 1] >= 0)
                ++this.fields[bombs[i] + 16 - 1];

            if (row < 15 && this.fields[bombs[i] + 16] >= 0)
                ++this.fields[bombs[i] + 16];

            if (row < 15 && column < 15 && this.fields[bombs[i] + 16 + 1] >= 0)
                ++this.fields[bombs[i] + 16 + 1];
        }
    }

    randBombs(pos: number) {
        let p: number = 0;
        let lst: Array<number> = [];

        for (let i = 0; i < 40; ++i) {
            do
                p = Math.floor(Math.random() * 255);
            while (lst.indexOf(p) >= 0 || this.isNeighbour(pos, p));

            lst.push(p);
        }

        return lst;
    }

    isNeighbour(pos1: number, pos2: number) {
        let row: number = Math.floor(pos1 / 16);
        let column: number = pos1 % 16;

        if (pos2 == pos1)
            return true;

        if (row > 0 && column > 0 && pos2 == pos1 - 16 - 1)
            return true;

        if (row > 0 && pos2 == pos1 - 16)
            return true;

        if (row > 0 && column < 15 && pos2 == pos1 - 16 + 1)
            return true;

        if (column > 0 && pos2 == pos1 - 1)
            return true;

        if (column < 15 && pos2 == pos1 + 1)
            return true;

        if (row < 15 && column > 0 && pos2 == pos1 + 16 - 1)
            return true;

        if (row < 15 && pos2 == pos1 + 16)
            return true;

        if (row < 15 && column < 15 && pos2 == pos1 + 16 + 1)
            return true;

        return false;
    }

    bfs(posBeg: number) {
        let queue: Array<number> = [posBeg];
        this.setVisible(posBeg);

        while (queue.length > 0) {
            let pos: number = queue.shift();
            let row: number = Math.floor(pos / 16);
            let column: number = pos % 16;

            if (this.fields[pos] == 0) {
                if (row > 0 && column > 0 && this.visible[pos - 16 - 1] == 0) {
                    this.setVisible(pos - 16 - 1);

                    if (this.fields[pos - 16 - 1] >= 0)
                        queue.push(pos - 16 - 1);
                }

                if (row > 0 && this.visible[pos - 16] == 0) {
                    this.setVisible(pos - 16);

                    if (this.fields[pos - 16] >= 0)
                        queue.push(pos - 16);
                }

                if (row > 0 && column < 15 && this.visible[pos - 16 + 1] == 0) {
                    this.setVisible(pos - 16 + 1);

                    if (this.fields[pos - 16 + 1] >= 0)
                        queue.push(pos - 16 + 1);
                }

                if (column > 0 && this.visible[pos - 1] == 0) {
                    this.setVisible(pos - 1);

                    if (this.fields[pos - 1] >= 0)
                        queue.push(pos - 1);
                }

                if (column < 15 && this.visible[pos + 1] == 0) {
                    this.setVisible(pos + 1);

                    if (this.fields[pos + 1] >= 0)
                        queue.push(pos + 1);
                }

                if (row < 15 && column > 0 && this.visible[pos + 16 - 1] == 0) {
                    this.setVisible(pos + 16 - 1);

                    if (this.fields[pos + 16 - 1] >= 0)
                        queue.push(pos + 16 - 1);
                }

                if (row < 15 && this.visible[pos + 16] == 0) {
                    this.setVisible(pos + 16);

                    if (this.fields[pos + 16] >= 0)
                        queue.push(pos + 16);
                }

                if (row < 15 && column < 15 && this.visible[pos + 16 + 1] == 0) {
                    this.setVisible(pos + 16 + 1);

                    if (this.fields[pos + 16 + 1] >= 0)
                        queue.push(pos + 16 + 1);
                }
            }
        }
    }

    setVisible(pos: number) {
        this.visible[pos] = 2;
        $("div#" + pos).css({ "border-style": "solid", "border-color": "#E6E6E6" });

        if (this.fields[pos] > 0)
            $("div#" + pos).html(String(this.fields[pos]));
    }

    flagSetting(pos: number) {
        if (this.visible[pos] == 0) {
            this.visible[pos] = 1;
            --this.flagsLeft;
            $("div#" + pos).css({ "background-color": "green" });

            if (this.fields[pos] == -1)
                ++this.shots;
        }
        else if (this.visible[pos] == 1) {
            this.visible[pos] = 0;
            ++this.flagsLeft;
            $("div#" + pos).css({ "background-color": "#BBBBBB" });

            if (this.fields[pos] == -1)
                --this.shots;
        }
    }

    isBomb(pos: number) {
        return this.fields[pos] == -1;
    }

    isEmpty(pos: number) {
        return this.fields[pos] == 0;
    }

    isNotVisible(pos: number) {
        return this.visible[pos] == 0;
    }
}

class TrollGame {
    private flags: Array<boolean>;
    flagsLeft: number;

    constructor() {
        this.restart();
    }

    restart() {
        this.flags = [];
        this.flagsLeft = 40;

        for (let i = 0; i < 256; ++i) {
            this.flags.push(false);
        }
    }

    isFlag(pos: number) {
        return this.flags[pos];
    }

    flagSetting(pos: number) {
        if (this.flags[pos]) {
            this.flags[pos] = false;
            ++this.flagsLeft;
            $("div#" + pos).css({ "background-color": "#DDDDDD" });
        }
        else {
            this.flags[pos] = true;
            --this.flagsLeft;
            $("div#" + pos).css({ "background-color": "green" });
        }
    }
}

function showBombsNormal() {
    $("div.field")
        .filter(function (ix: number, em: Element) {
            return normal.isBomb(parseInt(em.id, 10));
        })
        .css({
            "background-image": "url(\"images/bomba.jpg\")",
            "background-size": "100% 100%",
            "border-style": "solid"
        });
}

function showBombsTroll(pos: number) {
    let p: number = 0;
    let lst: Array<number> = [pos];

    for (let i = 0; i < 39; ++i) {
        do
            p = Math.floor(Math.random() * 255);
        while (lst.indexOf(p) >= 0);

        lst.push(p);
    }

    $("div.field")
        .filter(function (ix: number, em: Element) {
            return lst.indexOf(parseInt(em.id, 10)) >= 0;
        })
        .css({
            "background-image": "url(\"images/bomba.jpg\")",
            "background-size": "100% 100%",
            "border-style": "solid"
        });
}

function leftClickOnFieldNormal(element: Element) {
    let pos: number = parseInt(element.id, 10);

    if (normal.isNotVisible(pos)) {
        ++normal.clicks;
        $("div#clicks").html(String(normal.clicks));

        if (!normal.isReady)
            normal.prepare(pos);

        if (normal.isBomb(pos)) {
            showBombsNormal();
            endGame(false);
        }
        else if (normal.isEmpty(pos))
            normal.bfs(pos);
        else
            normal.setVisible(pos);
    }
}

function leftClickOnFieldTroll(element: Element) {
    let pos: number = parseInt(element.id, 10);

    if (!troll.isFlag(pos)) {
        showBombsTroll(pos);
        $("div#clicks").html("1");
        endGame(false);
    }
}

function middleClickOnFieldNormal(element: Element) {
    let pos: number = parseInt(element.id, 10);

    normal.flagSetting(pos);
    $("div#flags").html(String(normal.flagsLeft));

    if (normal.shots == 40)
        endGame(true);
}

function middleClickOnFieldTroll(element: Element) {
    let pos: number = parseInt(element.id, 10);

    troll.flagSetting(pos);
    $("div#flags").html(String(troll.flagsLeft));
}

function checkMouseOnFieldNormal(event: JQuery.Event<Element>) {
    if (event.which == 1)
        leftClickOnFieldNormal(event.target);
    else if (event.which == 2)
        middleClickOnFieldNormal(event.target);
}

function checkMouseOnFieldTroll(event: JQuery.Event<Element>) {
    if (event.which == 1)
        leftClickOnFieldTroll(event.target);
    else if (event.which == 2)
        middleClickOnFieldTroll(event.target);
}

function checkMouseOnFieldNone(event: JQuery.Event<Element>) {
}

function startNormal() {
    $("div.field").off("mousedown");
    normal.restart();

    $("div.field")
        .on("mousedown", checkMouseOnFieldNormal)
        .css({
            "background-color": "#BBBBBB",
            "background-image": "none",
            "border-style": "outset",
            "border-color": "black"
        })
        .html("");
    $("div.face").css({ "background-image": "url(\"images/epicface.jpg\")" }).on("click", startNormal);
    $("div#clicks").html(String(normal.clicks));
    $("div#flags").html(String(normal.flagsLeft));
    $("div.counter").on("click", startTroll);
}

function startTroll() {
    $("div.field").off("mousedown");
    troll.restart();

    $("div.field")
        .on("mousedown", checkMouseOnFieldTroll)
        .css({
            "background-color": "#DDDDDD",
            "background-image": "none",
            "border-style": "outset",
            "border-color": "black"
        })
        .html("");
    $("div.face").css({ "background-image": "url(\"images/trollface.jpg\")" }).on("click", startNormal);
    $("div#clicks").html("0");
    $("div#flags").html(String(troll.flagsLeft));
    $("div.counter").on("click", startTroll);
}

function endGame(correct: boolean) {
    $("div.field").off("mousedown");
    $("div.field").on("mousedown", checkMouseOnFieldNone);

    if (correct)
        $("div.face").css({ "background-image": "url(\"images/winface.jpg\")" });
    else
        $("div.face").css({ "background-image": "url(\"images/sadface.jpg\")" });
}

function startNewGame() {
    normal = new NormalGame();
    troll = new TrollGame();
    startNormal();
}

$(document).ready(startNewGame);
