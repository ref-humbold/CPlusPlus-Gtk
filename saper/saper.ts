/// <reference path="jquery.d.ts"/>

let board: Board = null;
let troll: Troll = null;

class Board {
    private fields: Array<number>;
    private visible: Array<number>;

    flagsLeft: number;
    clicks: number;
    shots: number;
    generated: boolean;

    constructor() {
    }

    restart() {
        this.fields = [];
        this.visible = [];
        this.flagsLeft = 40;
        this.clicks = 0;
        this.shots = 0;
        this.generated = false;

        for (let i = 0; i < 256; ++i) {
            this.fields.push(0);
            this.visible.push(0);
        }
    }

    prepare(pos: number) {
        let bombs = this.randBombs(pos);
        this.generated = true;

        for (let i = 0; i < bombs.length; ++i) {
            let w: number = Math.floor(bombs[i] / 16);
            let k: number = bombs[i] % 16;

            this.fields[bombs[i]] = -1;

            if (w > 0 && k > 0 && this.fields[bombs[i] - 16 - 1] >= 0)
                ++this.fields[bombs[i] - 16 - 1];

            if (w > 0 && this.fields[bombs[i] - 16] >= 0)
                ++this.fields[bombs[i] - 16];

            if (w > 0 && k < 15 && this.fields[bombs[i] - 16 + 1] >= 0)
                ++this.fields[bombs[i] - 16 + 1];

            if (k > 0 && this.fields[bombs[i] - 1] >= 0)
                ++this.fields[bombs[i] - 1];

            if (k < 15 && this.fields[bombs[i] + 1] >= 0)
                ++this.fields[bombs[i] + 1];

            if (w < 15 && k > 0 && this.fields[bombs[i] + 16 - 1] >= 0)
                ++this.fields[bombs[i] + 16 - 1];

            if (w < 15 && this.fields[bombs[i] + 16] >= 0)
                ++this.fields[bombs[i] + 16];

            if (w < 15 && k < 15 && this.fields[bombs[i] + 16 + 1] >= 0)
                ++this.fields[bombs[i] + 16 + 1];
        }
    }

    randBombs(pos: number) {
        let p: number = 0;
        let lst: Array<number> = [];

        for (let i = 0; i < 40; ++i) {
            do
                p = Math.floor(Math.random() * 255);
            while (lst.indexOf(p) >= 0 || this.isNeib(pos, p));

            lst.push(p);
        }

        return lst;
    }

    isNeib(pos1: number, pos2: number) {
        let w: number = Math.floor(pos1 / 16);
        let k: number = pos1 % 16;

        if (pos2 == pos1)
            return true;

        if (w > 0 && k > 0 && pos2 == pos1 - 16 - 1)
            return true;

        if (w > 0 && pos2 == pos1 - 16)
            return true;

        if (w > 0 && k < 15 && pos2 == pos1 - 16 + 1)
            return true;

        if (k > 0 && pos2 == pos1 - 1)
            return true;

        if (k < 15 && pos2 == pos1 + 1)
            return true;

        if (w < 15 && k > 0 && pos2 == pos1 + 16 - 1)
            return true;

        if (w < 15 && pos2 == pos1 + 16)
            return true;

        if (w < 15 && k < 15 && pos2 == pos1 + 16 + 1)
            return true;

        return false;
    }

    bfs(posBeg: number) {
        let queue: Array<number> = [posBeg];
        this.setVisible(posBeg);

        while (queue.length > 0) {
            let pos: number = queue.shift();
            let w: number = Math.floor(pos / 16);
            let k: number = pos % 16;

            if (this.fields[pos] == 0) {
                if (w > 0 && k > 0 && this.visible[pos - 16 - 1] == 0) {
                    this.setVisible(pos - 16 - 1);

                    if (this.fields[pos - 16 - 1] >= 0)
                        queue.push(pos - 16 - 1);
                }

                if (w > 0 && this.visible[pos - 16] == 0) {
                    this.setVisible(pos - 16);

                    if (this.fields[pos - 16] >= 0)
                        queue.push(pos - 16);
                }

                if (w > 0 && k < 15 && this.visible[pos - 16 + 1] == 0) {
                    this.setVisible(pos - 16 + 1);

                    if (this.fields[pos - 16 + 1] >= 0)
                        queue.push(pos - 16 + 1);
                }

                if (k > 0 && this.visible[pos - 1] == 0) {
                    this.setVisible(pos - 1);

                    if (this.fields[pos - 1] >= 0)
                        queue.push(pos - 1);
                }

                if (k < 15 && this.visible[pos + 1] == 0) {
                    this.setVisible(pos + 1);

                    if (this.fields[pos + 1] >= 0)
                        queue.push(pos + 1);
                }

                if (w < 15 && k > 0 && this.visible[pos + 16 - 1] == 0) {
                    this.setVisible(pos + 16 - 1);

                    if (this.fields[pos + 16 - 1] >= 0)
                        queue.push(pos + 16 - 1);
                }

                if (w < 15 && this.visible[pos + 16] == 0) {
                    this.setVisible(pos + 16);

                    if (this.fields[pos + 16] >= 0)
                        queue.push(pos + 16);
                }

                if (w < 15 && k < 15 && this.visible[pos + 16 + 1] == 0) {
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

class Troll {
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
            return board.isBomb(parseInt(em.id, 10));
        })
        .css({
            "background-image": "url(\"bomba.jpg\")",
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
            "background-image": "url(\"bomba.jpg\")",
            "background-size": "100% 100%",
            "border-style": "solid"
        });
}

function leftClickOnFieldNormal(element: Element) {
    let pos: number = parseInt(element.id, 10);

    if (board.isNotVisible(pos)) {
        ++board.clicks;
        $("div#clicks").html(String(board.clicks));

        if (!board.generated)
            board.prepare(pos);

        if (board.isBomb(pos)) {
            showBombsNormal();
            endGame(false);
        }
        else if (board.isEmpty(pos))
            board.bfs(pos);
        else
            board.setVisible(pos);
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

    board.flagSetting(pos);
    $("div#flags").html(String(board.flagsLeft));

    if (board.shots == 40)
        endGame(true);
}

function middleClickOnFieldTroll(element: Element) {
    let pos: number = parseInt(element.id, 10);

    troll.flagSetting(pos);
    $("div#flags").html(String(troll.flagsLeft));
}

function checkMouseOnFieldNormal(event: JQueryMouseEventObject) {
    if (event.which == 1)
        leftClickOnFieldNormal(event.target);
    else if (event.which == 2)
        middleClickOnFieldNormal(event.target);
}

function checkMouseOnFieldTroll(event: JQueryMouseEventObject) {
    if (event.which == 1)
        leftClickOnFieldTroll(event.target);
    else if (event.which == 2)
        middleClickOnFieldTroll(event.target);
}

function checkMouseOnFieldNone(event: JQueryMouseEventObject) {
}

function startNormal() {
    $("div.field").off("mousedown");
    board.restart();

    $("div.field")
        .on("mousedown", checkMouseOnFieldNormal)
        .css({
            "background-color": "#BBBBBB",
            "background-image": "none",
            "border-style": "outset",
            "border-color": "black"
        })
        .html("");
    $("div.face").css({ "background-image": "url(\"epicface.jpg\")" }).on("click", startNormal);
    $("div#clicks").html(String(board.clicks));
    $("div#flags").html(String(board.flagsLeft));
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
    $("div.face").css({ "background-image": "url(\"trollface.jpg\")" }).on("click", startNormal);
    $("div#clicks").html("0");
    $("div#flags").html(String(troll.flagsLeft));
    $("div.counter").on("click", startTroll);
}

function endGame(correct: boolean) {
    $("div.field").off("mousedown");
    $("div.field").on("mousedown", checkMouseOnFieldNone);

    if (correct)
        $("div.face").css({ "background-image": "url(\"winface.jpg\")" });
    else
        $("div.face").css({ "background-image": "url(\"sadface.jpg\")" });
}

function beginning() {
    board = new Board();
    troll = new Troll();
    startNormal();
}

$(document).ready(beginning);
