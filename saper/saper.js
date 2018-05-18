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
var board = null;
var Flag;
(function (Flag) {
    Flag[Flag["Hidden"] = 0] = "Hidden";
    Flag[Flag["Visible"] = 1] = "Visible";
    Flag[Flag["Flagged"] = 2] = "Flagged";
})(Flag || (Flag = {}));
var Board = /** @class */ (function () {
    function Board(background_colour, face_image) {
        this.background_colour = background_colour;
        this.face_image = face_image;
        this.beginNewGame();
    }
    Board.prototype.restart = function () {
        this.distances = [];
        this.flags = [];
        this.flagsLeft = Board.BOMBS_COUNT;
        this.clicks = 0;
        for (var i = 0; i < Board.SIZE * Board.SIZE; ++i) {
            this.distances.push(Board.DISTANCE_EMPTY);
            this.flags.push(Flag.Hidden);
        }
    };
    Board.prototype.leftClick = function (element) {
        ++this.clicks;
        $("div#clicks").html(String(this.clicks));
    };
    Board.prototype.middleClick = function (element) {
        var pos = parseInt(element.id, 10);
        this.changeFlag(pos);
        $("div#flags").html(String(this.flagsLeft));
    };
    Board.prototype.endGame = function (isWinning) {
        $("div.field").off("mousedown");
        $("div.field").on("mousedown", this.clickNothing);
        if (isWinning)
            $("div.face").css({ "background-image": "url(\"images/winface.jpg\")" });
        else {
            this.showBombs();
            $("div.face").css({ "background-image": "url(\"images/sadface.jpg\")" });
        }
    };
    Board.prototype.randBombs = function (count, posClicked, isOnClicked) {
        var pos = 0;
        var bombs = isOnClicked ? [posClicked] : [];
        var factor = Board.SIZE * Board.SIZE - 1;
        for (var i = 0; i < count; ++i) {
            do
                pos = Math.floor(Math.random() * factor);
            while (bombs.indexOf(pos) >= 0 || this.isNeighbour(posClicked, pos));
            bombs.push(pos);
        }
        return bombs;
    };
    Board.prototype.beginNewGame = function () {
        $("div.field").off("mousedown");
        this.restart();
        $("div.field")
            .on("mousedown", this.mouseClicked.bind(this))
            .css({
            "background-color": this.background_colour,
            "background-image": "none",
            "border-style": "outset",
            "border-color": "black"
        })
            .html("");
        $("div.face").css({ "background-image": this.face_image }).on("click", startNormalGame);
        $("div#clicks").html(String(this.clicks));
        $("div#flags").html(String(this.flagsLeft));
        $("div.counter").on("click", startTrollGame);
    };
    Board.prototype.mouseClicked = function (event) {
        if (event.which == Board.LEFT_MOUSE)
            this.leftClick(event.target);
        else if (event.which == Board.MIDDLE_MOUSE)
            this.middleClick(event.target);
    };
    Board.prototype.showBombs = function () {
        this.getFieldsWithBombs()
            .css({
            "background-image": "url(\"images/bomba.jpg\")",
            "background-size": "100% 100%",
            "border-style": "solid"
        });
    };
    Board.prototype.changeFlag = function (pos) {
        if (this.flags[pos] == Flag.Hidden) {
            this.flags[pos] = Flag.Flagged;
            --this.flagsLeft;
            $("div#" + pos).css({ "background-color": "green" });
            this.increaseShots(pos);
        }
        else if (this.flags[pos] == Flag.Flagged) {
            this.flags[pos] = Flag.Hidden;
            ++this.flagsLeft;
            $("div#" + pos).css({ "background-color": this.background_colour });
            this.decreaseShots(pos);
        }
    };
    Board.prototype.isNeighbour = function (pos1, pos2) {
        var row = Math.floor(pos1 / NormalBoard.SIZE);
        var column = pos1 % NormalBoard.SIZE;
        if (pos2 == pos1)
            return true;
        if (row > 0 && column > 0 && pos2 == pos1 - NormalBoard.SIZE - 1)
            return true;
        if (row > 0 && pos2 == pos1 - NormalBoard.SIZE)
            return true;
        if (row > 0 && column < NormalBoard.SIZE - 1 && pos2 == pos1 - NormalBoard.SIZE + 1)
            return true;
        if (column > 0 && pos2 == pos1 - 1)
            return true;
        if (column < NormalBoard.SIZE - 1 && pos2 == pos1 + 1)
            return true;
        if (row < NormalBoard.SIZE - 1 && column > 0 && pos2 == pos1 + NormalBoard.SIZE - 1)
            return true;
        if (row < NormalBoard.SIZE - 1 && pos2 == pos1 + NormalBoard.SIZE)
            return true;
        if (row < NormalBoard.SIZE - 1 && column < NormalBoard.SIZE - 1
            && pos2 == pos1 + NormalBoard.SIZE + 1)
            return true;
        return false;
    };
    Board.prototype.clickNothing = function (event) {
    };
    Board.LEFT_MOUSE = 1;
    Board.MIDDLE_MOUSE = 2;
    Board.DISTANCE_EMPTY = 0;
    Board.DISTANCE_BOMB = -1;
    Board.BOMBS_COUNT = 40;
    Board.SIZE = 16;
    return Board;
}());
var NormalBoard = /** @class */ (function (_super) {
    __extends(NormalBoard, _super);
    function NormalBoard() {
        return _super.call(this, "#BBBBBB", "url(\"images/epicface.jpg\")") || this;
    }
    NormalBoard.prototype.restart = function () {
        _super.prototype.restart.call(this);
        this.shots = 0;
        this.isGenerated = false;
    };
    NormalBoard.prototype.getFieldsWithBombs = function () {
        var _this = this;
        return $("div.field")
            .filter(function (index, elem) {
            return _this.isBomb(parseInt(elem.id, 10));
        });
    };
    NormalBoard.prototype.leftClick = function (element) {
        _super.prototype.leftClick.call(this, element);
        var pos = parseInt(element.id, 10);
        if (this.flags[pos] == Flag.Hidden) {
            if (!this.isGenerated)
                this.generate(pos);
            if (this.isBomb(pos)) {
                this.endGame(false);
            }
            else if (this.isEmpty(pos))
                this.bfs(pos);
            else
                this.setVisible(pos);
        }
    };
    NormalBoard.prototype.middleClick = function (element) {
        _super.prototype.middleClick.call(this, element);
        if (this.shots == 40)
            this.endGame(true);
    };
    NormalBoard.prototype.increaseShots = function (pos) {
        if (this.isBomb(this.distances[pos]))
            ++this.shots;
    };
    NormalBoard.prototype.decreaseShots = function (pos) {
        if (this.isBomb(this.distances[pos]))
            --this.shots;
    };
    NormalBoard.prototype.generate = function (startingPos) {
        var bombs = this.randBombs(NormalBoard.BOMBS_COUNT, startingPos, false);
        this.isGenerated = true;
        for (var i = 0; i < bombs.length; ++i) {
            var row = Math.floor(bombs[i] / NormalBoard.SIZE);
            var column = bombs[i] % NormalBoard.SIZE;
            this.distances[bombs[i]] = NormalBoard.DISTANCE_BOMB;
            if (row > 0 && column > 0
                && !this.isBomb(this.distances[bombs[i] - NormalBoard.SIZE - 1]))
                ++this.distances[bombs[i] - NormalBoard.SIZE - 1];
            if (row > 0 && !this.isBomb(this.distances[bombs[i] - NormalBoard.SIZE]))
                ++this.distances[bombs[i] - NormalBoard.SIZE];
            if (row > 0 && column < NormalBoard.SIZE - 1
                && !this.isBomb(this.distances[bombs[i] - NormalBoard.SIZE + 1]))
                ++this.distances[bombs[i] - NormalBoard.SIZE + 1];
            if (column > 0 && !this.isBomb(this.distances[bombs[i] - 1]))
                ++this.distances[bombs[i] - 1];
            if (column < NormalBoard.SIZE - 1 && !this.isBomb(this.distances[bombs[i] + 1]))
                ++this.distances[bombs[i] + 1];
            if (row < NormalBoard.SIZE - 1 && column > 0
                && !this.isBomb(this.distances[bombs[i] + NormalBoard.SIZE - 1]))
                ++this.distances[bombs[i] + NormalBoard.SIZE - 1];
            if (row < NormalBoard.SIZE - 1
                && !this.isBomb(this.distances[bombs[i] + NormalBoard.SIZE]))
                ++this.distances[bombs[i] + NormalBoard.SIZE];
            if (row < NormalBoard.SIZE - 1 && column < NormalBoard.SIZE - 1
                && !this.isBomb(this.distances[bombs[i] + NormalBoard.SIZE + 1]))
                ++this.distances[bombs[i] + NormalBoard.SIZE + 1];
        }
    };
    NormalBoard.prototype.bfs = function (posBeg) {
        var queue = [posBeg];
        this.setVisible(posBeg);
        while (queue.length > 0) {
            var pos = queue.shift();
            var row = Math.floor(pos / NormalBoard.SIZE);
            var column = pos % NormalBoard.SIZE;
            if (this.isEmpty(this.distances[pos])) {
                if (row > 0 && column > 0
                    && this.flags[pos - NormalBoard.SIZE - 1] == Flag.Hidden) {
                    this.setVisible(pos - NormalBoard.SIZE - 1);
                    if (!this.isBomb(this.distances[pos - NormalBoard.SIZE - 1]))
                        queue.push(pos - NormalBoard.SIZE - 1);
                }
                if (row > 0 && this.flags[pos - NormalBoard.SIZE] == Flag.Hidden) {
                    this.setVisible(pos - NormalBoard.SIZE);
                    if (!this.isBomb(this.distances[pos - NormalBoard.SIZE]))
                        queue.push(pos - NormalBoard.SIZE);
                }
                if (row > 0 && column < NormalBoard.SIZE - 1
                    && this.flags[pos - NormalBoard.SIZE + 1] == Flag.Hidden) {
                    this.setVisible(pos - NormalBoard.SIZE + 1);
                    if (!this.isBomb(this.distances[pos - NormalBoard.SIZE + 1]))
                        queue.push(pos - NormalBoard.SIZE + 1);
                }
                if (column > 0 && this.flags[pos - 1] == Flag.Hidden) {
                    this.setVisible(pos - 1);
                    if (!this.isBomb(this.distances[pos - 1]))
                        queue.push(pos - 1);
                }
                if (column < NormalBoard.SIZE - 1 && this.flags[pos + 1] == Flag.Hidden) {
                    this.setVisible(pos + 1);
                    if (!this.isBomb(this.distances[pos + 1]))
                        queue.push(pos + 1);
                }
                if (row < NormalBoard.SIZE - 1 && column > 0
                    && this.flags[pos + NormalBoard.SIZE - 1] == Flag.Hidden) {
                    this.setVisible(pos + NormalBoard.SIZE - 1);
                    if (!this.isBomb(this.distances[pos + NormalBoard.SIZE - 1]))
                        queue.push(pos + NormalBoard.SIZE - 1);
                }
                if (row < NormalBoard.SIZE - 1
                    && this.flags[pos + NormalBoard.SIZE] == Flag.Hidden) {
                    this.setVisible(pos + NormalBoard.SIZE);
                    if (!this.isBomb(this.distances[pos + NormalBoard.SIZE]))
                        queue.push(pos + NormalBoard.SIZE);
                }
                if (row < NormalBoard.SIZE - 1 && column < NormalBoard.SIZE - 1
                    && this.flags[pos + NormalBoard.SIZE + 1] == Flag.Hidden) {
                    this.setVisible(pos + NormalBoard.SIZE + 1);
                    if (!this.isBomb(this.distances[pos + NormalBoard.SIZE + 1]))
                        queue.push(pos + NormalBoard.SIZE + 1);
                }
            }
        }
    };
    NormalBoard.prototype.setVisible = function (pos) {
        this.flags[pos] = Flag.Visible;
        $("div#" + pos).css({ "border-style": "solid", "border-color": "#E6E6E6" });
        if (this.distances[pos] > 0)
            $("div#" + pos).html(String(this.distances[pos]));
    };
    NormalBoard.prototype.isBomb = function (pos) {
        return this.distances[pos] == Board.DISTANCE_BOMB;
    };
    NormalBoard.prototype.isEmpty = function (pos) {
        return this.distances[pos] == Board.DISTANCE_EMPTY;
    };
    return NormalBoard;
}(Board));
var TrollBoard = /** @class */ (function (_super) {
    __extends(TrollBoard, _super);
    function TrollBoard() {
        return _super.call(this, "#DDDDDD", "url(\"images/trollface.jpg\")") || this;
    }
    TrollBoard.prototype.restart = function () {
        _super.prototype.restart.call(this);
    };
    TrollBoard.prototype.getFieldsWithBombs = function () {
        var bombs = this.randBombs(NormalBoard.BOMBS_COUNT - 1, this.lastClickPos, true);
        return $("div.field")
            .filter(function (index, elem) {
            return bombs.indexOf(parseInt(elem.id, 10)) >= 0;
        });
    };
    TrollBoard.prototype.leftClick = function (element) {
        _super.prototype.leftClick.call(this, element);
        var pos = parseInt(element.id, 10);
        this.lastClickPos = pos;
        if (this.flags[pos] == Flag.Hidden) {
            this.endGame(false);
        }
    };
    TrollBoard.prototype.middleClick = function (element) {
        _super.prototype.middleClick.call(this, element);
    };
    TrollBoard.prototype.increaseShots = function (pos) {
    };
    TrollBoard.prototype.decreaseShots = function (pos) {
    };
    return TrollBoard;
}(Board));
function startNormalGame() {
    board = new NormalBoard();
}
function startTrollGame() {
    board = new TrollBoard();
}
$(document).ready(startNormalGame);
//# sourceMappingURL=saper.js.map