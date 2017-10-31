/// <reference path="jquery.d.ts" />
var board = null;
var troll = null;
var Board = (function() {
    function Board() {}
    Board.prototype.restart = function() {
        this.fields = [];
        this.visible = [];
        this.flagsLeft = 40;
        this.clicks = 0;
        this.shots = 0;
        this.generated = false;
        for (var i = 0; i < 256; ++i) {
            this.fields.push(0);
            this.visible.push(0);
        }
    };
    Board.prototype.prepare = function(pos) {
        var bombs = this.randBombs(pos);
        this.generated = true;
        for (var i = 0; i < bombs.length; ++i) {
            var w = Math.floor(bombs[i] / 16);
            var k = bombs[i] % 16;
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
    };
    Board.prototype.randBombs = function(pos) {
        var p = 0;
        var lst = [];
        for (var i = 0; i < 40; ++i) {
            do
                p = Math.floor(Math.random() * 255);
            while (lst.indexOf(p) >= 0 || this.isNeib(pos, p));
            lst.push(p);
        }
        return lst;
    };
    Board.prototype.isNeib = function(pos1, pos2) {
        var w = Math.floor(pos1 / 16);
        var k = pos1 % 16;
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
    };
    Board.prototype.bfs = function(posBeg) {
        var queue = [posBeg];
        this.setVisible(posBeg);
        while (queue.length > 0) {
            var pos = queue.shift();
            var w = Math.floor(pos / 16);
            var k = pos % 16;
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
    };
    Board.prototype.setVisible = function(pos) {
        this.visible[pos] = 2;
        $("div#" + pos).css({ "border-style": "solid", "border-color": "#E6E6E6" });
        if (this.fields[pos] > 0)
            $("div#" + pos).html(String(this.fields[pos]));
    };
    Board.prototype.flagSetting = function(pos) {
        if (this.visible[pos] == 0) {
            this.visible[pos] = 1;
            --this.flagsLeft;
            $("div#" + pos).css({ "background-color": "green" });
            if (this.fields[pos] == -1)
                ++this.shots;
        } else if (this.visible[pos] == 1) {
            this.visible[pos] = 0;
            ++this.flagsLeft;
            $("div#" + pos).css({ "background-color": "#BBBBBB" });
            if (this.fields[pos] == -1)
                --this.shots;
        }
    };
    Board.prototype.isBomb = function(pos) {
        return this.fields[pos] == -1;
    };
    Board.prototype.isEmpty = function(pos) {
        return this.fields[pos] == 0;
    };
    Board.prototype.isNotVisible = function(pos) {
        return this.visible[pos] == 0;
    };
    return Board;
}());
var Troll = (function() {
    function Troll() {
        this.restart();
    }
    Troll.prototype.restart = function() {
        this.flags = [];
        this.flagsLeft = 40;
        for (var i = 0; i < 256; ++i) {
            this.flags.push(false);
        }
    };
    Troll.prototype.isFlag = function(pos) {
        return this.flags[pos];
    };
    Troll.prototype.flagSetting = function(pos) {
        if (this.flags[pos]) {
            this.flags[pos] = false;
            ++this.flagsLeft;
            $("div#" + pos).css({ "background-color": "#DDDDDD" });
        } else {
            this.flags[pos] = true;
            --this.flagsLeft;
            $("div#" + pos).css({ "background-color": "green" });
        }
    };
    return Troll;
}());

function showBombsNormal() {
    $("div.field")
        .filter(function(ix, em) {
            return board.isBomb(parseInt(em.id, 10));
        })
        .css({
            "background-image": "url(\"bomba.jpg\")",
            "background-size": "100% 100%",
            "border-style": "solid"
        });
}

function showBombsTroll(pos) {
    var p = 0;
    var lst = [pos];
    for (var i = 0; i < 39; ++i) {
        do
            p = Math.floor(Math.random() * 255);
        while (lst.indexOf(p) >= 0);
        lst.push(p);
    }
    $("div.field")
        .filter(function(ix, em) {
            return lst.indexOf(parseInt(em.id, 10)) >= 0;
        })
        .css({
            "background-image": "url(\"bomba.jpg\")",
            "background-size": "100% 100%",
            "border-style": "solid"
        });
}

function leftClickOnFieldNormal(element) {
    var pos = parseInt(element.id, 10);
    if (board.isNotVisible(pos)) {
        ++board.clicks;
        $("div#clicks").html(String(board.clicks));
        if (!board.generated)
            board.prepare(pos);
        if (board.isBomb(pos)) {
            showBombsNormal();
            endGame(false);
        } else if (board.isEmpty(pos))
            board.bfs(pos);
        else
            board.setVisible(pos);
    }
}

function leftClickOnFieldTroll(element) {
    var pos = parseInt(element.id, 10);
    if (!troll.isFlag(pos)) {
        showBombsTroll(pos);
        $("div#clicks").html("1");
        endGame(false);
    }
}

function middleClickOnFieldNormal(element) {
    var pos = parseInt(element.id, 10);
    board.flagSetting(pos);
    $("div#flags").html(String(board.flagsLeft));
    if (board.shots == 40)
        endGame(true);
}

function middleClickOnFieldTroll(element) {
    var pos = parseInt(element.id, 10);
    troll.flagSetting(pos);
    $("div#flags").html(String(troll.flagsLeft));
}

function checkMouseOnFieldNormal(event) {
    if (event.which == 1)
        leftClickOnFieldNormal(event.target);
    else if (event.which == 2)
        middleClickOnFieldNormal(event.target);
}

function checkMouseOnFieldTroll(event) {
    if (event.which == 1)
        leftClickOnFieldTroll(event.target);
    else if (event.which == 2)
        middleClickOnFieldTroll(event.target);
}

function checkMouseOnFieldNone(event) {}

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

function endGame(correct) {
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