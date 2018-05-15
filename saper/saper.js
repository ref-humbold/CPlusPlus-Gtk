/// <reference path="jquery.d.ts"/>
var __extends = (this && this.__extends) || (function () {
    var extendStatics = Object.setPrototypeOf ||
        ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
        function (d, b) { for (var p in b) if (b.hasOwnProperty(p)) d[p] = b[p]; };
    return function (d, b) {
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
//#region
var board = null;
var Board = /** @class */ (function () {
    function Board() {
        this.restart();
    }
    Board.prototype.showBombs = function () {
        this.getFieldsWithBombs()
            .css({
            "background-image": "url(\"images/bomba.jpg\")",
            "background-size": "100% 100%",
            "border-style": "solid"
        });
    };
    Board.prototype.mouseClicked = function (event) {
        if (event.which == Board.LEFT_MOUSE)
            this.leftClick(event.target);
        else if (event.which == Board.MIDDLE_MOUSE)
            this.middleClick(event.target);
    };
    Board.prototype.leftClick = function (element) {
        this.lastClickPos = parseInt(element.id, 10);
    };
    Board.prototype.middleClick = function (element) {
        this.lastClickPos = parseInt(element.id, 10);
    };
    Board.prototype.endGame = function (isWinner) {
        $("div.field").off("mousedown");
        $("div.field").on("mousedown", this.clickNothing);
        if (isWinner)
            $("div.face").css({ "background-image": "url(\"images/winface.jpg\")" });
        else
            $("div.face").css({ "background-image": "url(\"images/sadface.jpg\")" });
    };
    Board.prototype.clickNothing = function (event) {
    };
    Board.LEFT_MOUSE = 1;
    Board.MIDDLE_MOUSE = 2;
    return Board;
}());
var NormalBoard = /** @class */ (function (_super) {
    __extends(NormalBoard, _super);
    function NormalBoard() {
        return _super.call(this) || this;
    }
    NormalBoard.prototype.restart = function () {
        this.fields = [];
        this.visible = [];
        this.flagsLeft = 40;
        this.clicks = 0;
        this.shots = 0;
        this.isReady = false;
        for (var i = 0; i < 256; ++i) {
            this.fields.push(0);
            this.visible.push(0);
        }
    };
    NormalBoard.prototype.getFieldsWithBombs = function () {
        var _this = this;
        return $("div.field")
            .filter(function (index, elem) {
            return _this.isBomb(parseInt(elem.id, 10));
        });
    };
    NormalBoard.prototype.leftClick = function (element) {
        throw new Error("Method not implemented.");
    };
    NormalBoard.prototype.middleClick = function (element) {
        throw new Error("Method not implemented.");
    };
    NormalBoard.prototype.isBomb = function (pos) {
        return this.fields[pos] == -1;
    };
    NormalBoard.prototype.isEmpty = function (pos) {
        return this.fields[pos] == 0;
    };
    NormalBoard.prototype.isNotVisible = function (pos) {
        return this.visible[pos] == 0;
    };
    return NormalBoard;
}(Board));
var TrollBoard = /** @class */ (function (_super) {
    __extends(TrollBoard, _super);
    function TrollBoard() {
        return _super.call(this) || this;
    }
    TrollBoard.prototype.restart = function () {
        throw new Error("Method not implemented.");
    };
    TrollBoard.prototype.getFieldsWithBombs = function () {
        var randPos = 0;
        var bombs = [this.lastClickPos];
        for (var i = 0; i < 39; ++i) {
            do
                randPos = Math.floor(Math.random() * 255);
            while (bombs.indexOf(randPos) >= 0);
            bombs.push(randPos);
        }
        return $("div.field")
            .filter(function (index, elem) {
            return bombs.indexOf(parseInt(elem.id, 10)) >= 0;
        });
    };
    TrollBoard.prototype.leftClick = function (element) {
        throw new Error("Method not implemented.");
    };
    TrollBoard.prototype.middleClick = function (element) {
        throw new Error("Method not implemented.");
    };
    return TrollBoard;
}(Board));
//#endregion
var normal = null;
var troll = null;
var NormalGame = /** @class */ (function () {
    function NormalGame() {
        this.restart();
    }
    NormalGame.prototype.restart = function () {
        this.fields = [];
        this.visible = [];
        this.flagsLeft = 40;
        this.clicks = 0;
        this.shots = 0;
        this.isReady = false;
        for (var i = 0; i < 256; ++i) {
            this.fields.push(0);
            this.visible.push(0);
        }
    };
    NormalGame.prototype.prepare = function (pos) {
        var bombs = this.randBombs(pos);
        this.isReady = true;
        for (var i = 0; i < bombs.length; ++i) {
            var row = Math.floor(bombs[i] / 16);
            var column = bombs[i] % 16;
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
    };
    NormalGame.prototype.randBombs = function (pos) {
        var p = 0;
        var lst = [];
        for (var i = 0; i < 40; ++i) {
            do
                p = Math.floor(Math.random() * 255);
            while (lst.indexOf(p) >= 0 || this.isNeighbour(pos, p));
            lst.push(p);
        }
        return lst;
    };
    NormalGame.prototype.isNeighbour = function (pos1, pos2) {
        var row = Math.floor(pos1 / 16);
        var column = pos1 % 16;
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
    };
    NormalGame.prototype.bfs = function (posBeg) {
        var queue = [posBeg];
        this.setVisible(posBeg);
        while (queue.length > 0) {
            var pos = queue.shift();
            var row = Math.floor(pos / 16);
            var column = pos % 16;
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
    };
    NormalGame.prototype.setVisible = function (pos) {
        this.visible[pos] = 2;
        $("div#" + pos).css({ "border-style": "solid", "border-color": "#E6E6E6" });
        if (this.fields[pos] > 0)
            $("div#" + pos).html(String(this.fields[pos]));
    };
    NormalGame.prototype.flagSetting = function (pos) {
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
    };
    NormalGame.prototype.isBomb = function (pos) {
        return this.fields[pos] == -1;
    };
    NormalGame.prototype.isEmpty = function (pos) {
        return this.fields[pos] == 0;
    };
    NormalGame.prototype.isNotVisible = function (pos) {
        return this.visible[pos] == 0;
    };
    return NormalGame;
}());
var TrollGame = /** @class */ (function () {
    function TrollGame() {
        this.restart();
    }
    TrollGame.prototype.restart = function () {
        this.flags = [];
        this.flagsLeft = 40;
        for (var i = 0; i < 256; ++i) {
            this.flags.push(false);
        }
    };
    TrollGame.prototype.isFlag = function (pos) {
        return this.flags[pos];
    };
    TrollGame.prototype.flagSetting = function (pos) {
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
    };
    return TrollGame;
}());
function showBombsNormal() {
    $("div.field")
        .filter(function (ix, em) {
        return normal.isBomb(parseInt(em.id, 10));
    })
        .css({
        "background-image": "url(\"images/bomba.jpg\")",
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
        .filter(function (ix, em) {
        return lst.indexOf(parseInt(em.id, 10)) >= 0;
    })
        .css({
        "background-image": "url(\"images/bomba.jpg\")",
        "background-size": "100% 100%",
        "border-style": "solid"
    });
}
function leftClickOnFieldNormal(element) {
    var pos = parseInt(element.id, 10);
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
    normal.flagSetting(pos);
    $("div#flags").html(String(normal.flagsLeft));
    if (normal.shots == 40)
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
function checkMouseOnFieldNone(event) {
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
function endGame(correct) {
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
//# sourceMappingURL=saper.js.map