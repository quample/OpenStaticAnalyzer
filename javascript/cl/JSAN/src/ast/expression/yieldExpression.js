/*
 *  This file is part of OpenStaticAnalyzer.
 *
 *  Copyright (c) 2004-2018 Department of Software Engineering - University of Szeged
 *
 *  Licensed under Version 1.2 of the EUPL (the "Licence");
 *
 *  You may not use this work except in compliance with the Licence.
 *
 *  You may obtain a copy of the Licence in the LICENSE file or at:
 *
 *  https://joinup.ec.europa.eu/software/page/eupl
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the Licence is distributed on an "AS IS" basis,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the Licence for the specific language governing permissions and
 *  limitations under the Licence.
 */

var globals = require('../../globals');
var factory = globals.getFactory();

module.exports = function (node, parent, firstVisit) {
    if (firstVisit) {
        if (globals.getWrapperOfNode(node) !== undefined) {
            return;
        }
        var yieldExpression = factory.createYieldExpressionWrapper(factory);
        globals.setPositionInfo(node, yieldExpression);
        yieldExpression.setDelegate(node.delegate);
        return yieldExpression;
    } else {
        var yieldExpressionWrapper = globals.getWrapperOfNode(node);
        yieldExpressionWrapper.setDelegate(node.delegate);
        if (node.argument != null) {
            var argumentWrapper = globals.getWrapperOfNode(node.argument);
            if (node.argument.type !== "Literal") {
                var argumentWrapperFunctionString = "setArgument" + node.argument.type;
            } else {
                var argumentWrapperFunctionString = "setArgument" + globals.getLiteralType(node.argument) + node.argument.type;
            }
            try {
                yieldExpressionWrapper[argumentWrapperFunctionString](argumentWrapper);
            } catch (e) {
                console.error("YIELDEXPRESSION - Function not exist: yieldExpressionWrapper." + argumentWrapperFunctionString + "! Reason of the error: " + e + "\n");
            }
        }

    }
}